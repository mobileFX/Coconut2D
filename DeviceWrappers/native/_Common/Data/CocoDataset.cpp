#include "CocoDataset.hpp"

#ifdef COCONUT2D_NET
#include "CocoHttpRequest.hpp"
#endif

#if ENABLE_VARIANT

// ==================================================================================================================================
//	 _    __           _             __
//	| |  / /___ ______(_)___ _____  / /______
//	| | / / __ `/ ___/ / __ `/ __ \/ __/ ___/
//	| |/ / /_/ / /  / / /_/ / / / / /_(__  )
//	|___/\__,_/_/  /_/\__,_/_/ /_/\__/____/
//
// ==================================================================================================================================

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT VariantToInt(VARIANT& v)
{
	switch (v.vt)
	{
	case VT_I1:		return (INT) v.cVal;
	case VT_I2:		return (INT) v.iVal;
	case VT_I4:		return (INT) v.lVal;
	case VT_I8:		return (INT) v.intVal;

	case VT_UI1:	return (INT) v.bVal;
	case VT_UI2:	return (INT) v.uiVal;
	case VT_UI4:	return (INT) v.ulVal;
	case VT_UI8:	return (INT) v.uintVal;

	case VT_R4:		return (INT) v.fltVal;
	case VT_R8:		return (INT) v.dblVal;

	case VT_CY:
	{
		char buff[255];
		sprintf(buff, "%ld", v.cyVal.Hi);
		return (INT64) atoi(buff);
	}
	case VT_BSTR:
	{
		char buff[255];
		sprintf(buff, "%s", _com_util::ConvertBSTRToString(v.bstrVal));
		return (INT64) atoi(buff);
	}
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DOUBLE VariantToDouble(VARIANT& v)
{
	switch (v.vt)
	{
	case VT_I1:		return (DOUBLE) v.cVal;
	case VT_I2:		return (DOUBLE) v.iVal;
	case VT_I4:		return (DOUBLE) v.lVal;
	case VT_I8:		return (DOUBLE) v.intVal;

	case VT_UI1:	return (DOUBLE) v.uintVal;
	case VT_UI2:	return (DOUBLE) v.uintVal;
	case VT_UI4:	return (DOUBLE) v.uintVal;
	case VT_UI8:	return (DOUBLE) v.uintVal;

	case VT_R4:		return (DOUBLE) v.fltVal;
	case VT_R8:		return (DOUBLE) v.dblVal;

	case VT_DECIMAL:
	{
		char buff[255];
		sprintf(buff, "%ld.%lu", v.decVal.Hi32, v.decVal.Lo32); break;
		return (DOUBLE) atof(buff);
	}
	break;

	case VT_CY:
	{
		char buff[255];
		sprintf(buff, "%ld.%lu", v.cyVal.Hi, v.cyVal.Lo); break;
		return (DOUBLE) atof(buff);
	}
	break;

	case VT_BSTR:
	{
		double d = wcstod(v.bstrVal, NULL);
		return (DOUBLE) d;
	}
	}

	return 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string VariantToString(VARIANT& v)
{
	switch (v.vt)
	{
	case VT_I1:
	case VT_I2:
	case VT_I4:
	case VT_I8:
	case VT_UI1:
	case VT_UI2:
	case VT_UI4:
	case VT_UI8:
	case VT_R4:
	case VT_R8:
	{
		DOUBLE d = VariantToDouble(v);
		char buff[255];
		sprintf(buff, "%g", d); break;
		return std::string(buff);
	}
	break;

	case VT_CY:
	{
		char buff[255];
		sprintf(buff, "%ld.%lu", v.cyVal.Hi, v.cyVal.Lo); break;
		return std::string(buff);
	}
	break;

	case VT_BSTR:
		return std::string(_com_util::ConvertBSTRToString(v.bstrVal));
		break;
	}

	return std::string("");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SYSTEMTIME VariantToDateTime(VARIANT& v)
{
	SYSTEMTIME st = { 0 };
	switch (v.vt)
	{
	case VT_DATE:
		VariantTimeToSystemTime(v.date, &st);
		break;

	case VT_BSTR:
		VARIANT dt;
		VariantInit(&dt);
		if (SUCCEEDED(parseDateTime(v.bstrVal, &dt)))
			VariantTimeToSystemTime(dt.date, &st);
		break;
	}

	return st;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT extractDate(const WCHAR* p, const WCHAR* *pStopped, SYSTEMTIME &tm)
{
	tm.wYear = (unsigned short) _wtoi(p);
	p = wcschr(p, '-');
	if (p && *++p)	// this checks we found the - and that there is a character after it
	{
		tm.wMonth = (unsigned short) _wtoi(p);
		p = wcschr(p, '-');
		if (p && *++p)
		{
			tm.wDay = (UINT) wcstol(p, const_cast<WCHAR **>(pStopped), 10);
			return S_OK;
		}
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT extractTime(const WCHAR* p, SYSTEMTIME &tm, long &offsetMins)
{
	int dir = -1, oMins = 0, oHrs = 0;
	tm.wHour = (unsigned short) _wtoi(p);
	p = wcschr(p, ':');
	if (p && *++p)
	{
		tm.wMinute = (unsigned short) _wtoi(p);
		p = wcschr(p, ':');
		if (p && *++p)
		{
			tm.wSecond = (unsigned short) _wtoi(p);
			const WCHAR * pOffsetStart = p;
			p = wcschr(p, '-');
			if (p)
				dir = 1;
			if (!p)
				p = wcschr(pOffsetStart, '+');
			if (p && *++p)
			{
				oHrs = _wtoi(p);
				p = wcschr(p, ':');
				if (p && *++p)
					oMins = _wtoi(p);
			}
			offsetMins = ((oHrs * 60) + oMins) * dir;
			return S_OK;
		}
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT SystemTimeToVariant(SYSTEMTIME &tm, long offsetMins, VARIANT* dest)
{
	CComVariant vdate;
	vdate.vt = VT_DATE;
	SystemTimeToVariantTime(&tm, &vdate.date);
	// now apply the offset
	double offset = offsetMins / (24 * 60.0f);
	vdate.date += offset;
	return vdate.Detach(dest);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT parseDateTime(BSTR charData, VARIANT* dest)
{
	// looking for yyyy-mm-ddThh:mm:ss-hh:mm or yyyy-mm-ddThh:mm:ssZ
	// min length is 20
	bool converted = false;
	const WCHAR * p = charData;
	if (SysStringLen(charData) >= 19)
	{
		SYSTEMTIME tm = { 0 };
		long offsetMins;
		if (SUCCEEDED(extractDate(charData, &p, tm)))
		{
			p = wcschr(p, 'T');
			if (p && *++p)
			{
				if (SUCCEEDED(extractTime(p, tm, offsetMins)))
					return SystemTimeToVariant(tm, offsetMins, dest);
			}
		}
	}
	// as a fall back, try the VARIANTCHANGETYPE on the string
	CComVariant v(charData);
	HRESULT hr = v.ChangeType(VT_DATE);
	if (FAILED(hr))
		return S_FALSE;
	return v.Detach(dest);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT parseDate(BSTR charData, VARIANT * dest)
{
	SYSTEMTIME tm = { 0 };
	const WCHAR * p = 0;
	if (SUCCEEDED(extractDate(charData, &p, tm)))
		return SystemTimeToVariant(tm, 0, dest);
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT parseTime(BSTR charData, VARIANT * dest)
{
	SYSTEMTIME tm = { 0 };
	long offsetMins;
	if (SUCCEEDED(extractTime(charData, tm, offsetMins)))
	{
		if (SUCCEEDED(SystemTimeToVariant(tm, offsetMins, dest)))
		{
			dest->date -= (long) (dest->date);
			return S_OK;
		}
	}
	return S_FALSE;
}

#endif

// ==================================================================================================================================
//	   ______                 ____        __        _____ __
//	  / ____/___  _________  / __ \____ _/ /_____ _/ ___// /_________  ____ _____ ___
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/\__ \/ __/ ___/ _ \/ __ `/ __ `__ \
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ /___/ / /_/ /  /  __/ /_/ / / / / / /
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_//____/\__/_/   \___/\__,_/_/ /_/ /_/
//
// ==================================================================================================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDataStream::CocoDataStream()
{
	__className = String("CocoDataStream");
	__offset = 0;
	__length = 0;
	bi = new Int32Array(__length);
	bf = new Float32Array(bi->buffer);
	#ifdef COCONUT2D_NET
	http = nullptr;
	#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDataStream::~CocoDataStream()
{
	#ifdef COCONUT2D_NET
	COCO_DELETE_OBJECT(http);
	#endif

	COCO_DELETE_OBJECT(bf);
	COCO_DELETE_OBJECT(bi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::write(const void* bytes, UINT size)
{
	__offset = 0;
	__length = size / 4;

	if (bf) bf = (delete bf, nullptr);
	if (bi) bi = (delete bi, nullptr);

	bi = new Int32Array(__length);
	memcpy(bi->buffer->data, bytes, size);
	bf = new Float32Array(bi->buffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* CocoDataStream::read(UINT& size)
{
	size = bi->length * bi->BYTES_PER_ELEMENT;
	void* buff = malloc(size);
	memcpy(buff, bi->buffer->data, size);
	return buff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef COCONUT2D_NET
Boolean CocoDataStream::openFromURL(String url, Boolean async)
{
	Boolean ret = false;
	if (!async)
	{
		http = new CocoHttpRequest;
		http->xhttp->open("GET", url, false);
		http->xhttp->send();
		if (http->Success() && http->Ready())
		{
			ret = openFromArrayBuffer(http->__get_responseBuffer());
		}
	}
	else
	{
		http = new CocoHttpRequest;
		http->xhttp->__get_responseType() = "arraybuffer";
		http->xhttp->open("GET", url, true);
		http->xhttp->send();
		ret = true;
	}
	return ret;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
Boolean CocoDataStream::__get_Ready()
{
	Boolean ret = false;

	#ifdef COCONUT2D_NET
	if (http && http->Ready())
	{
		if (http->Success())
		{
			ret = openFromArrayBuffer(http->__get_responseBuffer());
		}
		COCO_DELETE_OBJECT(http);
	}
	else
	#endif

	{
		ret = __length > 0;
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Boolean CocoDataStream::openFromArrayBuffer(ArrayBuffer* data)
{
	if (!data || data->byteLength == 0)
	{
		return false;
	}
	COCO_DELETE_OBJECT(bf);
	COCO_DELETE_OBJECT(bi);
	bi = new Int32Array(data);
	bf = new Float32Array(bi->buffer);
	__offset = 0;
	__length = bi->byteLength;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Int32Array* CocoDataStream::__get_buffer()
{
	return bi;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::increaseSize(Integer s)
{
	if (__offset + s <= __length)
	{
		return;
	}
	__length = __offset + s;
	if (__offset + s <= bi->length)
	{
		return;
	}
	Int32Array* nbi = new Int32Array(bi->length + ELEMENTS_INCREMENT + s);
	nbi->set(bi);
	COCO_DELETE_OBJECT(bf);
	COCO_DELETE_OBJECT(bi);
	bi = nbi;
	bf = new Float32Array(bi->buffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::shrink()
{
	if (bi->length == __length)
	{
		return;
	}
	Int32Array* nbi = new Int32Array(__length);
	nbi->set(bi);
	COCO_DELETE_OBJECT(bf);
	COCO_DELETE_OBJECT(bi);
	bi = nbi;
	bf = new Float32Array(bi->buffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Integer CocoDataStream::__get_offset()
{
	return __offset;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::__set_offset(Integer v)
{
	__offset = v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::writeInteger(Integer v)
{
	increaseSize(1);
	(*bi)[__offset++] = v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::writeFloat(Float v)
{
	increaseSize(1);
	(*bf)[__offset++] = v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::writeString(String v)
{
	Boolean isNull = (v == NULL_DATA_VALUE);
	Integer L = (isNull ? -1 : v.size());
	writeInteger(L);
	for (Integer i = 0; i < L; i++)
	{
		Integer c = v.charCodeAt(i);
		writeInteger(c);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::writeBoolean(Boolean v)
{
	writeInteger(v ? 1 : 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::writeInt32Array(Int32Array* v)
{
	writeInteger(v->length);
	increaseSize(v->length);
	bi->set(v, __offset);
	__offset += v->length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::writeFloat32Array(Float32Array* v)
{
	writeInteger(v->length);
	increaseSize(v->length);
	bf->set(v, __offset);
	__offset += v->length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::writeDataStream(CocoDataStream* v)
{
	v->shrink();
	writeInt32Array(v->bi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDataStream* CocoDataStream::readCocoDataStream()
{
	Int32Array* data = readInt32Array();
	CocoDataStream* ret = new CocoDataStream;
	ret->set(data);
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataStream::set(Int32Array* v)
{
	COCO_DELETE_OBJECT(bf);
	COCO_DELETE_OBJECT(bi);
	bi = new Int32Array(v->length);
	bi->set(v);
	bf = new Float32Array(bi->buffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Uint8Array* CocoDataStream::readUint8Array()
{
	if (__offset + 1 > __length)
	{
		return nullptr;
	}
	Integer L = readInteger();
	if (__offset + L > __length)
	{
		return nullptr;
	}
	Uint8Array* ret = new Uint8Array(bi->buffer, __offset * 4, L);
	__offset += static_cast<Integer>(static_cast<Float>(L) / 4.0f);
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Int32Array* CocoDataStream::readInt32Array()
{
	if (__offset + 1 > __length)
	{
		return nullptr;
	}
	Integer L = readInteger();
	if (__offset + L > __length)
	{
		return nullptr;
	}
	Int32Array* ret = new Int32Array(bi->buffer, __offset * 4, L);
	__offset += L;
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Float32Array* CocoDataStream::readFloat32Array()
{
	if (__offset + 1 > __length)
	{
		return nullptr;
	}
	Integer L = readInteger();
	if (__offset + L > __length)
	{
		return nullptr;
	}
	Float32Array* ret = new Float32Array(bi->buffer, __offset * 4, L);
	__offset += L;
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Integer CocoDataStream::readInteger()
{
	if (__offset + 1 > __length)
	{
		return 0;
	}
	return (*bi)[__offset++];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Float CocoDataStream::readFloat()
{
	if (__offset + 1 > __length)
	{
		return 0.0f;
	}
	return (*bf)[__offset++];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDataStream::readString()
{
	if (__offset + 1 > __length)
	{
		return "";
	}
	Integer L = readInteger();
	if (L == -1)
	{
		return NULL_DATA_VALUE;
	}
	if (__offset + L > __length)
	{
		return "";
	}
	String ret = "";
	for (Integer i = 0; i < L; i++)
	{
		Integer c = readInteger();
		ret += String::fromCharCode(c);
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Boolean CocoDataStream::readBoolean()
{
	if (__offset + 1 > __length)
	{
		return false;
	}
	Integer i = readInteger();
	return i ? true : false;
}

// ==================================================================================================================================
//	   ______                 ____        __                  __
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __/
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /_
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/
//
// ==================================================================================================================================

String CocoDataset::LOCAL_NULL_DATA_VALUE(NULL_DATA_VALUE);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDataset::CocoDataset() : INDEX_TABLE(this)
{
	db=NULL;
	stringForNull = "null";
	UpdateInTransaction = true;
	EnableHighPerformance = false;
	RequeryOnUpdate = true;
	PrimaryKeyIndex = false;
	EnableUTF8 = true;
	EnableMatrixMode = true;
	needs_reindex = true;
	StatusFilter = SQLITE_RECORD_STATUS::RECORD_EDITABLE;
	UPDATE_SQL_DIRECTIVE = "UPDATE";
	INSERT_SQL_DIRECTIVE = "INSERT";
	DELETE_SQL_DIRECTIVE = "DELETE";
	isADO = false;
	close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDataset::~CocoDataset()
{
	close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataset::sqlite3_unbase64_fn(sqlite3_context *f, int nargs, sqlite3_value ** args)
{
	if (nargs != 1)
	{
		sqlite3_result_error(f, "BASE64_DECODE required exactly 1 argument", -1);
		return;
	}
	char* t = (char*) sqlite3_value_text(args[0]);
	int len=0;
	std::vector<uint8_t>* data = fromBase64(t);
	sqlite3_result_blob(f, data->data(), data->size(), SQLITE_TRANSIENT);
	delete data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::reopen()
{
	if(db) return true;
	if(fileName.size()>0)
	{
		int rc = sqlite3_open_v2(fileName.c_str(), &db, SQLITE_OPEN_READWRITE|SQLITE_OPEN_FULLMUTEX|SQLITE_OPEN_CREATE, NULL);
		sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
		sqlite3_extended_result_codes(db, true);

		if(EnableHighPerformance)
		{
			sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA default_cache_size=65536", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA cache_size=8192", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA page_size=8192", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA threads=8", NULL, NULL, NULL);
			sqlite3_exec(db, "PRAGMA case_sensitive_like=true", NULL, NULL, NULL);
			sqlite3_enable_shared_cache(true);
		}

		setLastError();
		return (rc==SQLITE_OK);
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDataset::requery(const bool& useBookmark)
{
	bool success = false;
	if(SQL)
	{
		String bookmark = getBookmark();
		needs_reindex = success = open(fileName, SQL);
		if(success && useBookmark && bookmark.size()>0) setBookmark(bookmark);
	}
	return success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::transactionBegin()
{
	if(!reopen()) return false;
	char* zErrMsg = NULL;
	int rc = sqlite3_exec(db, "BEGIN DEFERRED TRANSACTION;", NULL, NULL, &zErrMsg);
	if(zErrMsg) lastError = String(zErrMsg);
	return rc==SQLITE_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::transactionCommit()
{
	if(!reopen()) return false;
	char* zErrMsg = NULL;
	int rc = sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, &zErrMsg);
	if(zErrMsg) lastError = String(zErrMsg);
	return rc==SQLITE_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::transactionRollback(const String& savepointName)
{
	if(!reopen()) return false;
	char* zErrMsg = NULL;
	String SQL("ROLLBACK TRANSACTION");
	if(savepointName!="") SQL += " TO SAVEPOINT " + savepointName;
	SQL+=";";
	int rc = sqlite3_exec(db, SQL.c_str(), NULL, NULL, &zErrMsg);
	if(zErrMsg) lastError = String(zErrMsg);
	return rc==SQLITE_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::savepointCreate(const String& name)
{
	if(!reopen()) return false;
	char* zErrMsg = NULL;
	String SQL("SAVEPOINT " + name + ";");
	int rc = sqlite3_exec(db, SQL.c_str(), NULL, NULL, &zErrMsg);
	if(zErrMsg) lastError = String(zErrMsg);
	return rc==SQLITE_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::savepointRelease(const String& name)
{
	if(!reopen()) return false;
	char* zErrMsg = NULL;
	String SQL("RELEASE SAVEPOINT " + name + ";");
	int rc = sqlite3_exec(db, SQL.c_str(), NULL, NULL, &zErrMsg);
	if(zErrMsg) lastError = String(zErrMsg);
	return rc==SQLITE_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ENABLE_VARIANT
bool CocoDataset::open(VARIANT* vBytes)
{
	close();
	if(vBytes->vt!=(VT_ARRAY|VT_UI1)) return false;
	SAFEARRAY* psa = V_ARRAY(vBytes);
	long lBound, uBound;
	SafeArrayGetLBound(psa, 1, &lBound);
	SafeArrayGetUBound(psa, 1, &uBound);
	int cbBytesLen = uBound - lBound + 1;
	void* blob;
	SafeArrayAccessData(psa, &blob);
	open(blob, cbBytesLen);
	SafeArrayUnaccessData(psa);
	return true;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef COCONUT2D_NET
#include "XMLHttpRequest.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
Boolean CocoDataset::openURL(String url, Boolean async)
{
	Boolean ret = false;
	if (!async)
	{
		ds = new CocoDataStream;
		if (ds->openFromURL(url, false))
		{
			ret = openFromDataStream(ds);
		}
		COCO_DELETE_OBJECT(ds);
	}
	else
	{
		ds = new CocoDataStream;
		ret = ds->openFromURL(url, true);
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::updateURL(String url)
{
	ArrayBuffer* ab = toArrayBuffer();
	if (ab)
	{
		XMLHttpRequest* http = new XMLHttpRequest;
		http->open("POST", url, false);
		http->setRequestHeader("Content-Type", "plain/text");
		http->send(toBase64());
	}
	return true;
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::__get_Ready()
{
	bool ret = false;
	if (ds)
	{
		if (ds->__get_Ready())
		{
			ret = openFromDataStream(ds);
			COCO_DELETE_OBJECT(ds);
		}
	}
	else
	{
		ret = (METADATA.size() > 0);
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::openFromArrayBuffer(ArrayBuffer* ab)
{
	Boolean ret = false;
	CocoDataStream* ds = new CocoDataStream;
	if (ds->openFromArrayBuffer(ab))
	{
		ret = openFromDataStream(ds);
	}
	COCO_DELETE_OBJECT(ds);
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::openFromDataStream(CocoDataStream* ds)
{
	close();
	Integer i = 0;
	Integer recordCount = 0;
	Integer filedCount = 0;
	if (ds->readString() == "SQLiteRowset.1")
	{
		fileName = ds->readString();
		SQL = ds->readString();
		ACCESS = static_cast<SQLITE_TABLE_ACCESS>(ds->readInteger());
		filedCount = ds->readInteger();
		for (i = 0; i < filedCount; i++)
		{
			CocoDatasetField* COL = new CocoDatasetField(this);
			COL->read(*ds);
			METADATA.push_back(COL);
		}
		recordCount = ds->readInteger();
		for (i = 0; i < recordCount; i++)
		{
			CocoDatasetRow* ROW = new CocoDatasetRow(this);
			ROW->read(*ds);
			DATA.push_back(ROW);
		}
		moveFirst();
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::open(String fileName, String SQL)
{
	close();

	if (fileName.charCodeAt(0) == '.')
		fileName = CocoAssetFile::filesPath + fileName.substr(2);

	int rc = sqlite3_open_v2(fileName.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_CREATE, NULL);
	setLastError();
	if(rc!=SQLITE_OK) return false;

	sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
	sqlite3_exec(db, "PRAGMA cache_size=500000;", NULL, NULL, NULL);
	sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, NULL);
	sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, NULL);
	sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, NULL);

	this->fileName = fileName;
	this->SQL = SQL;

	// If no SQL return without closing the database (batch mode)
	if(SQL=="")
		return true;

	if(SQL.find("SELECT")==0 || SQL.find("select")==0)
	{
		// SELECT statement
		return select(SQL);
	}
	else
	{
		// CREATE, UPDATE, DELETE, INSERT, etc.
		return exec(SQL);
	}

	close();
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int sqlite_callback_exec(void *NotUsed, int argc, char **argv, char **azColName)
{
	CocoDataset* ROWSET = (CocoDataset*) NotUsed;
	if(ROWSET)
	{
		int i;

		if(!ROWSET->METADATA.size())
			for(i=0; i<argc; i++)
				ROWSET->ADD_META(i, String(azColName[i]));

		CocoDatasetRow* ROW = new CocoDatasetRow(ROWSET);
		for(i=0;i<argc;i++)
			ROW->FieldValues[i] = String::fromUTF8(argv[i]);
		ROWSET->DATA.push_back(ROW);
	}
	return 0;
}

bool CocoDataset::exec(const String& SQL, const bool& keepDatabaseOpen)
{
	if(!reopen()) return false;
	lastError = "";
	char* utf8 = (char*) SQL.toUTF8();
	char* zErrMsg = NULL;
	int rc = sqlite3_exec(db, utf8, sqlite_callback_exec, this, &zErrMsg);
	if(zErrMsg) lastError = String(zErrMsg);
	free(utf8);
	if(!keepDatabaseOpen)
	{
		sqlite3_close_v2(db);
		db=NULL;
	}
	return (rc==SQLITE_OK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::select(const String& SQL)
{
	close();
	if(!reopen()) return false;

	lastError = "";

	// Install support for BLOB
	int rc = sqlite3_create_function(db, "BASE64_DECODE", -1, SQLITE_UTF8, NULL, &sqlite3_unbase64_fn, NULL, NULL);
	setLastError();

	// =========================================================================
	// Check SQL statement
	// =========================================================================
	sqlite3_stmt* stmt;
	rc = sqlite3_complete(SQL.c_str());
	setLastError();
	if(true)
	{
		// =========================================================================
		// SQL statement is valid, prepare the SQL statement
		// =========================================================================
		rc = sqlite3_prepare_v2(db, SQL.c_str(), -1, &stmt, nullptr);
		setLastError();
		if(rc==SQLITE_OK)
		{
			// =========================================================================
			// Get Column Metadata
			// =========================================================================
			int fieldCount = sqlite3_column_count(stmt);

			// Create Metadata object for each Column:
			for(int FieldOrdinal=0; FieldOrdinal<fieldCount; FieldOrdinal++)
			{
				CocoDatasetField* DATA_COLUMN = new CocoDatasetField(this);

				// Get Column table and name (UTF8)
				const char* table = sqlite3_column_table_name(stmt,FieldOrdinal);
				const char* column = sqlite3_column_origin_name(stmt,FieldOrdinal);
				const char* alias = sqlite3_column_name(stmt, FieldOrdinal);

				if(table!=NULL && column!=NULL)
				{
					String base_table_name(table);
					String base_column_name(column);
					String alias_column_name(alias);

					// Now read complete column metadata
					if(!DATA_COLUMN->InitColumnMetadata(db, base_table_name, base_column_name, alias_column_name, FieldOrdinal))
						goto ErrorCleanUp;
				}
				else
				{
					if(!DATA_COLUMN->InitExpressionColumnMetadata(db, stmt, FieldOrdinal))
						goto ErrorCleanUp;
				}

				// Add data column info to Metadata
				METADATA.push_back(DATA_COLUMN);
			}

			// =========================================================================
			// Execute SQLite Statement and Retrieve Data one row at a time
			// =========================================================================
			for(rc = sqlite3_step(stmt);rc!=SQLITE_OK && rc!=SQLITE_DONE && rc!=SQLITE_ERROR;rc = sqlite3_step(stmt))
			{
				CocoDatasetRow* RECORD = new CocoDatasetRow(this);
				if(RECORD->load(stmt))
				{
					DATA.push_back(RECORD);
				}
				else
					goto ErrorCleanUp;
			}

			// Done with this statement
			rc = sqlite3_finalize(stmt);
		}
		else
			goto ErrorCleanUp;
	}
	else
		goto ErrorCleanUp;

	// All OK!

	sqlite3_close_v2(db);
	db=NULL;

	needs_reindex = DATA.size()>0;
	__recordIndex = needs_reindex ? 0 : -1;

	return moved();

ErrorCleanUp:
	setLastError();
	close();
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoDataset::recordCount(const SQLITE_RECORD_STATUS& Status)
{
	if(Status==RECORD_ALL)
		return DATA.size();

	int recordCount = 0;
	int i, L = DATA.size();
	for(i=0;i<L;i++)
		if(isSet(DATA[i]->STATUS, Status))
			recordCount++;

	return recordCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoDataset::row_to_record(const int& rowIndex, const SQLITE_RECORD_STATUS& Status)
{
	int r=-1, i, L = DATA.size();
	for(i=0; i<L; i++)
		if(isSet(DATA[i]->STATUS, Status))
			if(++r==rowIndex)
				break;
	return i;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDataset::getMatrix(const int& Row, const int& Col)
{
	// Convert data binding row (eg. the row of a data grid) to an actual record index.
	// We need to do this mapping because data grids usually filter records (eg. do not display deleted records)

	__recordIndex = row_to_record(Row, StatusFilter);
	if(!moved()) return NULL_DATA_VALUE;

	if(__recordIndex>=0 && __recordIndex<(int)DATA.size() && Col>=0 && Col<(int)METADATA.size())
	{
		String value = DATA[__recordIndex]->FieldValues[Col];

		if(value==NULL_DATA_VALUE)
			value = stringForNull;

		return value;
	}
	return String(NULL_DATA_VALUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::putMatrix(const int& Row, const int& Col, const String& value)
{
	// Convert data binding row (eg. the row of a data grid) to an actual record index.
	// We need to do this mapping because data grids usually filter records (eg. do not display deleted records)

	__recordIndex = row_to_record(Row, StatusFilter);

	if (__recordIndex >= 0 && __recordIndex<(int) DATA.size() && Col >= 0 && Col<(int) METADATA.size() && DATA[__recordIndex]->STATUS != SQLITE_RECORD_STATUS::RECORD_DELETED)
	{
		if (value == stringForNull)
		{
			if (DATA[__recordIndex]->FieldValues[Col] != NULL_DATA_VALUE)
			{
				DATA[__recordIndex]->FieldValues[Col] = NULL_DATA_VALUE;

				if (DATA[__recordIndex]->STATUS != SQLITE_RECORD_STATUS::RECORD_INSERTED)
					DATA[__recordIndex]->STATUS = SQLITE_RECORD_STATUS::RECORD_CHANGED;

				needs_reindex = true;
			}
		}
		else
		{
			if (DATA[__recordIndex]->FieldValues[Col] != value)
			{
				DATA[__recordIndex]->FieldValues[Col] = value;

				if (DATA[__recordIndex]->STATUS != SQLITE_RECORD_STATUS::RECORD_INSERTED)
					DATA[__recordIndex]->STATUS = SQLITE_RECORD_STATUS::RECORD_CHANGED;

				needs_reindex = true;
			}

		}

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String & CocoDataset::getValue(const int& RecordIndex, const int& Ordinal)
{
	if (RecordIndex >= 0 && RecordIndex<(int) DATA.size() && Ordinal >= 0 && Ordinal<(int) METADATA.size())
	{
		String & value = DATA[RecordIndex]->FieldValues[Ordinal];

		if(value==NULL_DATA_VALUE)
			value = stringForNull;

		return value;
	}
	return LOCAL_NULL_DATA_VALUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::putValue(const int& RecordIndex, const int& Ordinal, const String& value)
{
	if (RecordIndex >= 0 && RecordIndex<(int) DATA.size() && Ordinal >= 0 && Ordinal<(int) METADATA.size() && DATA[RecordIndex]->STATUS != SQLITE_RECORD_STATUS::RECORD_DELETED)
	{
		if (value == stringForNull)
		{
			if (DATA[RecordIndex]->FieldValues[Ordinal] != NULL_DATA_VALUE)
			{
				DATA[RecordIndex]->FieldValues[Ordinal] = NULL_DATA_VALUE;

				if (DATA[RecordIndex]->STATUS != SQLITE_RECORD_STATUS::RECORD_INSERTED)
					DATA[RecordIndex]->STATUS = SQLITE_RECORD_STATUS::RECORD_CHANGED;

				needs_reindex = true;
			}
		}
		else
		{
			if (DATA[RecordIndex]->FieldValues[Ordinal] != value)
			{
				DATA[RecordIndex]->FieldValues[Ordinal] = value;

				if (DATA[RecordIndex]->STATUS != SQLITE_RECORD_STATUS::RECORD_INSERTED)
					DATA[RecordIndex]->STATUS = SQLITE_RECORD_STATUS::RECORD_CHANGED;

				needs_reindex = true;
			}
		}

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SQLITE_RECORD_STATUS CocoDataset::status()
{
	if (__recordIndex >= 0 && __recordIndex<(int) DATA.size())
		return DATA[__recordIndex]->STATUS;
	else
		return SQLITE_RECORD_STATUS::RECORD_NO_RECORD;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::modified()
{
	int recordCount = DATA.size();
	for(int i=0; i<recordCount; i++)
		if(DATA[i]->STATUS!=SQLITE_RECORD_STATUS::RECORD_UNCHANGED)
			return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::move(const int& recordIndex)
{
	if (recordIndex >= 0 && recordIndex<(int) DATA.size())
	{
		__recordIndex = recordIndex;
		return moved();
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::moveFirst()
{
	__recordIndex=0;
	return moved();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::moveLast()
{
	__recordIndex = DATA.size()-1;
	return moved();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::moveNext()
{
	__recordIndex++;
	return moved();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::movePrev()
{
	__recordIndex--;
	return moved();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::first()
{
	moveFirst();
	if(!isSet(status(), RECORD_EDITABLE))
		next();
	return !DB_EOF;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::next()
{
	do
	{
		moveNext();
	}
	while (!DB_EOF && !isSet(status(), RECORD_EDITABLE));

	return !DB_EOF;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::moved()
{
	int records = DATA.size();

	if(records==0)
	{
		DB_EOF = true;
		DB_BOF = true;
		__recordIndex = -1;
		return true;
	}

	if(records>0 && __recordIndex>=records) __recordIndex = records;
	if(records>0 && __recordIndex<0) __recordIndex = 0;

	DB_BOF = (records>0 && __recordIndex==0);
	DB_EOF = (records>0 && __recordIndex==records);

	return (records>0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetField* CocoDataset::field(const String& name)
{
	String nb_name(name);
	NO_BRACKETS(nb_name);

	int fields = METADATA.size();
	if(fields>0)
	{
		for(int i=0; i<fields; i++)
		{
			CocoDatasetField* COL = METADATA[i];
			if(COL!=NULL)
			{
				if(COL->NAME == name || COL->ID == name) return COL;

				String fname(COL->NAME);
				NO_BRACKETS(fname);

				String fid(COL->ID);
				NO_BRACKETS(fid);

				if((fname == nb_name)||(fid == nb_name)) return COL;
			}
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetField* CocoDataset::field(const int& ordinal)
{
	int fields = METADATA.size();
	if(fields>0 && ordinal>=0 && ordinal<fields)
	{
		return METADATA[ordinal];
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetField* CocoDataset::fieldByName(const String& name)
{
	return field(name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetField* CocoDataset::fieldByIndex(Integer ordinal)
{
	Integer fields = METADATA.size();
	if(fields > 0 && ordinal >= 0 && ordinal < fields)
	{
		return METADATA[ordinal];
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ENABLE_VARIANT
VARIANT CocoDataset::getVariant(const int& ORDINAL)
{
	VARIANT pVal;
	VariantInit(&pVal);
	pVal.vt = VT_NULL;

	if (__recordIndex >= 0 && __recordIndex<(int) DATA.size() && ORDINAL >= 0 && ORDINAL<(int) METADATA.size())
	{
		CocoDatasetRow* RECORD = DATA[__recordIndex];

		if(RECORD->FieldValues[ORDINAL]!=NULL_DATA_VALUE)
		{
			switch(METADATA[ORDINAL]->SQLITE_DATATYPE)
			{
			case SQLITE_INTEGER:
				{
					int ivalue = atoi(RECORD->FieldValues[ORDINAL].c_str());
					InitVariantFromInt32(ivalue, &pVal);
				}
				break;

			case SQLITE_FLOAT:
				{
					double dvalue = atof(RECORD->FieldValues[ORDINAL].c_str());
					InitVariantFromDouble(dvalue, &pVal);
				}
				break;

			case SQLITE_BLOB:
				{
					String buff = RECORD->FieldValues[ORDINAL];
					InitVariantFromBuffer(buff.c_str(), buff.length(), &pVal);
				}
				break;

			default:
			case SQLITE_TEXT:
				{
					CComBSTR svalue(_com_util::ConvertStringToBSTR(RECORD->FieldValues[ORDINAL].c_str()));
					InitVariantFromString(svalue, &pVal);
				}
				break;
			}
		}
	}
	return pVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::putVariant(const int& ORDINAL, VARIANT& newVal, bool AffectStatus)
{
	if (!(__recordIndex >= 0 && __recordIndex<(int) DATA.size() && ORDINAL >= 0 && ORDINAL<(int) METADATA.size()))
		return false;

	CocoDatasetRow* RECORD = DATA[__recordIndex];

	return putVariant(RECORD, ORDINAL, newVal, AffectStatus);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::putVariant(CocoDatasetRow* RECORD, const int& ORDINAL, VARIANT& newVal, bool AffectStatus)
{
	if(RECORD->STATUS==RECORD_DELETED) return false;

	if(AffectStatus)
	{
		if(RECORD->STATUS==RECORD_UNCHANGED)
			RECORD->STATUS = RECORD_CHANGED;
	}

	CocoDatasetField* COL = METADATA[ORDINAL];
	String OldValue = RECORD->FieldValues[ORDINAL];


	if(!IS_KEY_COLUMN(COL) && newVal.vt==VT_BSTR && wcscmp(newVal.bstrVal,LNULL_DATA_VALUE)==0)
	{
		RECORD->FieldValues[ORDINAL] = NULL_DATA_VALUE;
	}
	else if(newVal.vt==VT_NULL || newVal.vt==VT_EMPTY)
	{
		RECORD->FieldValues[ORDINAL] = NULL_DATA_VALUE;
	}
	else if(IS_KEY_COLUMN(COL) && IS_AUTO_INCREMENT(COL))
	{
		if(RECORD->FieldValues[ORDINAL]==NULL_DATA_VALUE)
			RECORD->FieldValues[ORDINAL] = NEXT_IDENTITY();
	}
	else if(!IS_KEY_COLUMN(COL) || (IS_KEY_COLUMN(COL) && !IS_AUTO_INCREMENT(COL)))
	{
		switch(METADATA[ORDINAL]->TYPE)
		{
		case VARTYPE_I1:
		case VARTYPE_I2:
		case VARTYPE_I4:
		case VARTYPE_I8:
			{
				char buff[255];
				sprintf(buff, "%d", VariantToInt(newVal));
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;

		case VARTYPE_UI1:
		case VARTYPE_UI2:
		case VARTYPE_UI4:
		case VARTYPE_UI8:
			{
				char buff[255];
				sprintf(buff, "%u", VariantToInt(newVal));
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;

		case VARTYPE_DECIMAL:
		case VARTYPE_CY:
		case VARTYPE_R4:
		case VARTYPE_R8:
			{
				char buff[255];
				sprintf(buff, "%g", VariantToDouble(newVal));
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;

		case VARTYPE_BOOL:
			{
				if(newVal.vt==VT_BOOL)
				{
					BOOL boolVal = FALSE;
					VariantToBoolean(newVal, &boolVal);
					RECORD->FieldValues[ORDINAL] = boolVal==TRUE ? "1" : "0";
				}
				else
				{
					String b = VariantToString(newVal);
					std::transform(b.begin(), b.end(), b.begin(), ::tolower);
					if(b=="0" || b=="false" || b=="no" || b=="")
						RECORD->FieldValues[ORDINAL] = "0";
					else
						RECORD->FieldValues[ORDINAL] = "1";
				}
				break;
			}
			break;

		case VARTYPE_DATE:
			{
				char buff[255];
				SYSTEMTIME st = VariantToDateTime(newVal);
				sprintf(buff, "%4.4d-%2.2d-%2.2d", st.wYear, st.wMonth, st.wDay);
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;

		case VARTYPE_TIME:
			{
				char buff[255];
				SYSTEMTIME st = VariantToDateTime(newVal);
				sprintf(buff, "%2.2d:%2.2d:%2.2d", st.wHour, st.wMinute, st.wSecond);
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;

		case VARTYPE_TIMESTAMP:
			{
				char buff[255];
				SYSTEMTIME st = VariantToDateTime(newVal);
				sprintf(buff, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;

		case VARTYPE_DATETIME:
			{
				char buff[255];
				SYSTEMTIME st = VariantToDateTime(newVal);
				sprintf(buff, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;

		case VARTYPE_BLOB:
			break;

		case VARTYPE_STRING:
			{
				String buff = VariantToString(newVal);
				if(COL->LENGTH>0)
					buff=buff.substr(0, COL->LENGTH);
				RECORD->FieldValues[ORDINAL] = buff;
			}
			break;
		}
	}

	needs_reindex = true;
	return true;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDataset::DEFAULT(const int& Ordinal)
{
	if(METADATA[Ordinal]->DEFAULTVALUE=="GETDATE()" || METADATA[Ordinal]->DEFAULTVALUE=="TODAY()")
	{
		char buff[255];
		SYSTEMTIME st;

		#if WIN32_APPLICATION
		GetLocalTime(&st);
		#endif

		sprintf(buff, "%4.4d-%2.2d-%2.2d", st.wYear, st.wMonth, st.wDay);
		return buff;
	}
	else if(METADATA[Ordinal]->DEFAULTVALUE=="GETTIME()")
	{
		char buff[255];
		SYSTEMTIME st;

		#if WIN32_APPLICATION
		GetLocalTime(&st);
		#endif

		sprintf(buff, "%2.2d:%2.2d:%2.2d", st.wHour, st.wMinute, st.wSecond);
		return buff;
	}
	else if(METADATA[Ordinal]->DEFAULTVALUE=="GETTIMESTAMP()")
	{
		char buff[255];
		SYSTEMTIME st;

		#if WIN32_APPLICATION
		GetLocalTime(&st);
		#endif

		sprintf(buff, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		return buff;
	}
	else if(METADATA[Ordinal]->DEFAULTVALUE=="GETDATETIME()" || METADATA[Ordinal]->DEFAULTVALUE=="NOW()")
	{
		char buff[255];
		SYSTEMTIME st;

		#if WIN32_APPLICATION
		GetLocalTime(&st);
		#endif

		sprintf(buff, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		return buff;
	}
	else if(METADATA[Ordinal]->DEFAULTVALUE!="")
	{
		return METADATA[Ordinal]->DEFAULTVALUE;
	}
	else
		return NULL_DATA_VALUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::insertRecord()
{
	if((ACCESS & SQLITE_TABLE_ACCESS::CAN_INSERT)!=SQLITE_TABLE_ACCESS::CAN_INSERT)
		return false;

	if(METADATA.size())
	{
		CocoDatasetRow* RECORD = new CocoDatasetRow(this);
		RECORD->STATUS = RECORD_INSERTED;
		int KF = KEY_COLUMN_ORDINAL();

		for(int i=0, L=METADATA.size(); i<L; i++)
		{
			RECORD->FieldValues[i] = DEFAULT(i);
		}

		if(KF>=0 && METADATA[KF]->SQLITE_DATATYPE==SQLITE_VT_INTGER)
			RECORD->FieldValues[KF] = NEXT_IDENTITY();

		DATA.push_back(RECORD);
		needs_reindex = true;

		__recordIndex = DATA.size()-1;
		moved();

		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::deleteRecord()
{
	if((ACCESS & SQLITE_TABLE_ACCESS::CAN_DELETE)!=SQLITE_TABLE_ACCESS::CAN_DELETE)
		return false;

	int recordCount = DATA.size();

	if(METADATA.size() && __recordIndex>=0 && __recordIndex<recordCount)
	{
		CocoDatasetRow* Record = DATA[__recordIndex];

		if(Record->STATUS == RECORD_INSERTED)
		{
			// If the record is a new but uncommitted record we can safely delete it
			DATA.erase(DATA.begin()+__recordIndex);
			recordCount--;
			delete Record;
		}
		else
		{
			// If the record is not new (therefore is committed) we mark it for deletion
			Record->STATUS = RECORD_DELETED;
		}

		needs_reindex = true;

		if(recordCount==0)
		{
			moved();
		}
		else if(__recordIndex >= recordCount)
		{
			moveLast();
		}

		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoDataset::deleteRecords(const String& FieldName, const String& FieldValue)
{
	if((ACCESS & SQLITE_TABLE_ACCESS::CAN_DELETE)!=SQLITE_TABLE_ACCESS::CAN_DELETE)
		return 0;

	CocoDatasetField* F = field(FieldName);
	if(!F) return 0;

	int Ordinal = F->ORDINAL;
	int DeletedRecords = 0;
	CocoDatasetRow* Record;

	for(int RecordIndex=DATA.size()-1; RecordIndex>=0; RecordIndex--)
	{
		Record = DATA[RecordIndex];

		if(Record->FieldValues[Ordinal]==FieldValue)
		{
			switch(Record->STATUS)
			{
			case RECORD_UNCHANGED:
			case RECORD_CHANGED:
				Record->STATUS = RECORD_DELETED;
				DeletedRecords++;
				break;

			case RECORD_INSERTED:
				DATA.erase(DATA.begin()+RecordIndex);
				delete Record;
				DeletedRecords++;
				break;

			case RECORD_DELETED:
				break;
			}
		}
	}

	if(DeletedRecords)
		needs_reindex = true;

	moveFirst();

	return DeletedRecords;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CocoDataset::update_sql(std::stringstream& SQL)
{
	lastError = "";

	int fieldCount = METADATA.size();
	int recordCount = DATA.size();
	if(fieldCount==0 || recordCount==0) return;

	if(UpdateInTransaction)
		SQL << "\nBEGIN TRANSACTION;\n";

	// Do not update if no Key Column exists
	int KF = KEY_COLUMN_ORDINAL();
	if(KF==-1) return;
	CocoDatasetField* KEY_COLUMN = METADATA[KF];

	int i,r;
	CocoDatasetRow* pRow;
	CocoDatasetField* col;
	String ID;
	bool first = false;

	for(r=0; r<recordCount; r++)
	{
		pRow = DATA[r];
		ID = SQL_VALUE(r, KEY_COLUMN);

		switch (pRow->STATUS)
		{
			//------------------------------------------------------------
		case RECORD_NO_RECORD:
		case RECORD_UNCHANGED:
			break;

			//------------------------------------------------------------
		case RECORD_INSERTED:
			{
				SQL << INSERT_SQL_DIRECTIVE << " INTO " << KEY_COLUMN->BASETABLENAME << " (";
				first = false;
				for(i=0; i<fieldCount; i++)
				{
					col = METADATA[i];
					if(IS_KEY_COLUMN(col) && IS_AUTO_INCREMENT(col)) continue;
					if(col->BASETABLENAME==KEY_COLUMN->BASETABLENAME)
					{
						if(first) SQL << ",";
						SQL << col->BASECOLUMNNAME;
						first=true;
					}
				}
				SQL << ") VALUES (";
				first = false;
				for(i=0; i<fieldCount; i++)
				{
					col = METADATA[i];
					if(IS_KEY_COLUMN(col) && IS_AUTO_INCREMENT(col)) continue;
					if(col->BASETABLENAME==KEY_COLUMN->BASETABLENAME)
					{
						if(first) SQL << ",";
						SQL << SQL_VALUE(r,col);
						first=true;
					}
				}
				SQL << ");\n";
			}
			break;

			//------------------------------------------------------------
		case RECORD_CHANGED:

			// To change a row it must have a key column
			if(KF==-1) continue;

			for(i=0; i<fieldCount; i++)
			{
				col = METADATA[i];
				if(IS_KEY_COLUMN(col) && IS_AUTO_INCREMENT(col)) continue;
				if(col->BASETABLENAME==KEY_COLUMN->BASETABLENAME)// && Data[i]!=OrigData[i])
				{
					SQL << UPDATE_SQL_DIRECTIVE << " " << col->BASETABLENAME << " SET " << col->BASECOLUMNNAME << " = " << SQL_VALUE(r,col) << " WHERE " << KEY_COLUMN->ID << " = " << ID << ";\n";
				}
			}
			break;

			//------------------------------------------------------------
		case RECORD_DELETED:

			// To delete a row it must have a key column
			if(KF==-1) continue;
			SQL << DELETE_SQL_DIRECTIVE << " FROM " << KEY_COLUMN->BASETABLENAME << " WHERE " << KEY_COLUMN->ID << " = " << ID + ";\n";
			break;
		}
	}

	if(UpdateInTransaction)
		SQL << "\nCOMMIT TRANSACTION;";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::update()
{
	int RecordsAffected = 0;
	int UpdateErrors = 0;
	return update(RecordsAffected, UpdateErrors);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::update(int& RecordsAffected, int& UpdateErrors)
{
	bool result = false;
	if(reopen())
	{
		result = __internal_update(db, RecordsAffected, UpdateErrors);
		sqlite3_close_v2(db);
		db=NULL;
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::checkDuplicateIDs(CocoDatasetField* KEY_COLUMN)
{
	bool duplicate_ids = false;
	String ID;
	std::map<String, bool> IDs;
	CocoDatasetRow* record;
	int KF = KEY_COLUMN->ORDINAL;
	for(int i=0, L=DATA.size(); i<L; i++)
	{
		record = DATA[i];
		if(isSet(record->STATUS, RECORD_EDITABLE))
		{
			ID = record->FieldValues[KF];
			if(IDs[ID])
			{
				duplicate_ids = true;
				debugPrint("ERROR: duplicate value on column %s with id '%s'\n", KEY_COLUMN->NAME.c_str(), ID.c_str());
			}
			else
			{
				IDs[ID] = true;
			}
		}
	}
	return duplicate_ids;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::__internal_update(sqlite3* db, int& RecordsAffected, int& UpdateErrors)
{
	RecordsAffected = 0;
	UpdateErrors = 0;

	if((ACCESS & SQLITE_TABLE_ACCESS::CAN_UPDATE)!=SQLITE_TABLE_ACCESS::CAN_UPDATE)
		return false;

	int field_count = METADATA.size();
	int record_count = DATA.size();

	if(!field_count || !record_count)
		return false;

	bool error=false, first = false;
	int FieldIndex, ParamIndex=0, rc;
	CocoDatasetField* COL;
	CocoDatasetRow* RECORD;
	char* zErrMsg = NULL;

	lastError = "";

	//----------------------------------------------------------------------------------------------------
	// Ensure Database is open
	//----------------------------------------------------------------------------------------------------
	if(!db || field_count==0 || record_count==0) return false;

	//----------------------------------------------------------------------------------------------------
	// Do not update if no Key Column exists
	//----------------------------------------------------------------------------------------------------
	int KEY_FIELD_INDEX = KEY_COLUMN_ORDINAL();
	if(KEY_FIELD_INDEX==-1) return false;

	CocoDatasetField* KEY_COLUMN = METADATA[KEY_FIELD_INDEX];

	#ifdef NDEBUG
	checkDuplicateIDs(KEY_COLUMN);
	#endif

	//----------------------------------------------------------------------------------------------------
	// Prepare the INSERT, UPDATE and DELETE statements
	//----------------------------------------------------------------------------------------------------

	String SQL;

	sqlite3_stmt* DELETE_STMT;
	sqlite3_stmt* INSERT_STMT;
	sqlite3_stmt* UPDATE_STMT;

	std::stringstream DELETE_SQL;
	std::stringstream INSERT_SQL;
	std::stringstream UPDATE_SQL;

	std::vector<CocoDatasetField*> UPDATEABLE_FIELDS;

	DELETE_SQL << DELETE_SQL_DIRECTIVE
			   << " FROM " << KEY_COLUMN->BASETABLENAME
			   << " WHERE " << KEY_COLUMN->ID << " = ?1;";

	SQL = DELETE_SQL.str();
	rc = sqlite3_prepare_v2(db, SQL.c_str(), SQL.size(), &DELETE_STMT, NULL);

	INSERT_SQL << INSERT_SQL_DIRECTIVE << " INTO " << KEY_COLUMN->BASETABLENAME << " (";
	UPDATE_SQL << UPDATE_SQL_DIRECTIVE << " " << KEY_COLUMN->BASETABLENAME << " SET ";

	for(FieldIndex=0; FieldIndex<field_count; FieldIndex++)
	{
		COL = METADATA[FieldIndex];
		if(IS_KEY_COLUMN(COL) && IS_AUTO_INCREMENT(COL)) continue;
		if(COL->BASETABLENAME==KEY_COLUMN->BASETABLENAME)
		{
			UPDATEABLE_FIELDS.push_back(COL);
			if(first)
			{
				INSERT_SQL << ",";
				UPDATE_SQL << ",";
			}
			INSERT_SQL << COL->BASECOLUMNNAME;
			UPDATE_SQL << COL->BASECOLUMNNAME << "=?" << (++ParamIndex);
			first=true;
		}
	}
	INSERT_SQL << ") VALUES (";
	UPDATE_SQL << " WHERE " << KEY_COLUMN->ID << "=?" << (++ParamIndex) << ";";

	first = false;
	field_count = UPDATEABLE_FIELDS.size();

	for(FieldIndex=0; FieldIndex<field_count; FieldIndex++)
	{
		if(first) INSERT_SQL << ",";
		INSERT_SQL << "?" << (FieldIndex+1);
		first=true;
	}

	INSERT_SQL << ");";

	SQL = INSERT_SQL.str();
	debugPrint("%s\n", SQL.c_str());
	rc = sqlite3_prepare_v2(db, SQL.c_str(), SQL.size(), &INSERT_STMT, NULL);

	SQL = UPDATE_SQL.str();
	debugPrint("%s\n", SQL.c_str());
	rc = sqlite3_prepare_v2(db, SQL.c_str(), SQL.size(), &UPDATE_STMT, NULL);

	//----------------------------------------------------------------------------------------------------
	// Begin Transaction
	//----------------------------------------------------------------------------------------------------
	if(UpdateInTransaction)
	{
		zErrMsg = NULL;
		rc = sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &zErrMsg);
	}

	//----------------------------------------------------------------------------------------------------
	// Update (DELETED)
	//----------------------------------------------------------------------------------------------------
	for(ROWSET_DATA_ITER irecord=DATA.begin(), E=DATA.end(); irecord!=E; irecord++)
	{
		RECORD = *irecord;

		switch (RECORD->STATUS)
		{
		case RECORD_DELETED:
			if(KEY_FIELD_INDEX==-1) continue;
			update_bind_value(DELETE_STMT, RECORD, KEY_COLUMN, 1);
			if(!update_step(DELETE_STMT, RECORD, RecordsAffected, UpdateErrors)) goto RollbackUpdate;
			break;
		}
	}

	//----------------------------------------------------------------------------------------------------
	// Update (INSERTED / CHANGED)
	//----------------------------------------------------------------------------------------------------
	for(ROWSET_DATA_ITER irecord=DATA.begin(), E=DATA.end(); irecord!=E; irecord++)
	{
		RECORD = *irecord;

		switch (RECORD->STATUS)
		{
		//------------------------------------------------------------
		case RECORD_INSERTED:
			for(FieldIndex=0; FieldIndex<field_count; FieldIndex++)
				update_bind_value(INSERT_STMT, RECORD, UPDATEABLE_FIELDS[FieldIndex], FieldIndex+1);
			if(!update_step(INSERT_STMT, RECORD, RecordsAffected, UpdateErrors)) goto RollbackUpdate;
			break;

		//------------------------------------------------------------
		case RECORD_CHANGED:
			if(KEY_FIELD_INDEX==-1) continue;
			for(FieldIndex=0; FieldIndex<field_count; FieldIndex++)
				update_bind_value(UPDATE_STMT, RECORD, UPDATEABLE_FIELDS[FieldIndex], FieldIndex+1);
			update_bind_value(UPDATE_STMT, RECORD, KEY_COLUMN, field_count+1);
			if(!update_step(UPDATE_STMT, RECORD, RecordsAffected, UpdateErrors)) goto RollbackUpdate;
			break;

		}
	}


	//----------------------------------------------------------------------------------------------------
	// Commit Transaction
	//----------------------------------------------------------------------------------------------------
	if(UpdateInTransaction)
	{
		zErrMsg = NULL;
		rc = sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, &zErrMsg);
		setLastError();
	}

	//----------------------------------------------------------------------------------------------------
	// Normalize Dataset
	//----------------------------------------------------------------------------------------------------
	if(!zErrMsg)
	{
		if(RecordsAffected)
			needs_reindex = true;

		goto FinishUpdate;
	}

	//----------------------------------------------------------------------------------------------------
	// Rollback Transaction
	//----------------------------------------------------------------------------------------------------
RollbackUpdate:
	error = true;
	rc = sqlite3_exec(db, "ROLLBACK TRANSACTION;", NULL, NULL, NULL);

	//----------------------------------------------------------------------------------------------------
	// Deallocate
	//----------------------------------------------------------------------------------------------------
FinishUpdate:
	rc = sqlite3_finalize(DELETE_STMT);
	rc = sqlite3_finalize(INSERT_STMT);
	rc = sqlite3_finalize(UPDATE_STMT);

	//----------------------------------------------------------------------------------------------------
	// Done, Requery
	//----------------------------------------------------------------------------------------------------
	return error ? false : (RequeryOnUpdate ? requery() : true);
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDataset::update_step(sqlite3_stmt* stmt, CocoDatasetRow* ROW, int& RecordsAffected, int& UpdateErrors)
{
	int rc = sqlite3_step(stmt);
	sqlite3_reset(stmt);
	if(rc==SQLITE_DONE)
	{
		RecordsAffected++;
		return true;
	}

	UpdateErrors++;

	String msg;

	switch(ROW->STATUS)
	{
	case RECORD_INSERTED:
		msg = "inserting record";
		break;

	case RECORD_DELETED:
		msg = "deleting record";
		break;

	case RECORD_CHANGED:
		msg = "updating record";
		break;
	}

	switch(rc)
	{
	case SQLITE_CONSTRAINT_CHECK:			msg = "SQLite CONSTRAINT_CHECK error " + msg; break;
	case SQLITE_CONSTRAINT_COMMITHOOK:		msg = "SQLite CONSTRAINT_COMMITHOOK error " + msg; break;
	case SQLITE_CONSTRAINT_FOREIGNKEY:		msg = "SQLite CONSTRAINT_FOREIGNKEY error " + msg; break;
	case SQLITE_CONSTRAINT_FUNCTION:		msg = "SQLite CONSTRAINT_FUNCTION error " + msg; break;
	case SQLITE_CONSTRAINT_NOTNULL:			msg = "SQLite CONSTRAINT_NOTNULL error " + msg; break;
	case SQLITE_CONSTRAINT_PRIMARYKEY:		msg = "SQLite CONSTRAINT_PRIMARYKEY error " + msg; break;
	case SQLITE_CONSTRAINT_TRIGGER:			msg = "SQLite CONSTRAINT_TRIGGER error " + msg; break;
	case SQLITE_CONSTRAINT_UNIQUE:			msg = "SQLite CONSTRAINT_UNIQUE error " + msg; break;
	case SQLITE_CONSTRAINT_VTAB:			msg = "SQLite CONSTRAINT_VTAB error " + msg; break;
	case SQLITE_CONSTRAINT_ROWID:			msg = "SQLite CONSTRAINT_ROWID error " + msg; break;
	}

	msg += " for record index " + String(ROW->recordIndex) + "\n";
	for(int i=0, L=METADATA.size(); i<L; i++)
		msg += METADATA[i]->NAME + " = "	+ ROW->FieldValues[i] + "\n";

	msg = std::string(80, '-') + "\n" + msg;
	debugPrint(msg.c_str());

	lastError = msg;
	return false;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDataset::update_bind_value(sqlite3_stmt* stmt, CocoDatasetRow* Row, CocoDatasetField* Col, int pIndex)
{
	String& value = Row->FieldValues[Col->ORDINAL];

	if(value==NULL_DATA_VALUE)
	{
		sqlite3_bind_null(stmt, pIndex);
		return true;
	}

	switch(Col->SQLITE_DATATYPE)
	{
	case SQLITE_VT_INTGER:
		{
			int ivalue = atoi(value.c_str());
			sqlite3_bind_int(stmt, pIndex, ivalue);
		}
		return true;

	case SQLITE_VT_FLOAT:
		{
			double dvalue = atof(value.c_str());
			sqlite3_bind_double(stmt, pIndex, dvalue);
		}
		return true;

	case SQLITE_VT_TEXT:
		{
			if(EnableUTF8)
			{
				const char* utf8 = value.toUTF8();
				sqlite3_bind_text(stmt, pIndex, utf8, -1, SQLITE_TRANSIENT);
				free((void*)utf8);
			}
			else
			{
				sqlite3_bind_text(stmt, pIndex, value.c_str(), value.size(), SQLITE_STATIC);
			}
		}
		return true;

	case SQLITE_VT_BLOB:
		return false;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDataset::normalize()
{
	debugPrint("Begin Dataset Normalization: %d records\n", DATA.size());

	// Change record status
	bool normalized = false;
	ROWSET_DATA_ITER begin = DATA.begin();
	CocoDatasetRow* record;
	for(int record_index=DATA.size()-1; record_index>=0; record_index--)
	{
		record = DATA[record_index];
		switch(record->STATUS)
		{
		case RECORD_CHANGED:
		case RECORD_INSERTED:
			record->STATUS = RECORD_UNCHANGED;
			 normalized = true;
			break;

		case RECORD_DELETED:
			DATA.erase(begin+record_index);
			delete record;
			normalized = true;
			break;
		}
	}
	moveFirst();

	needs_reindex = true;

	debugPrint("End Dataset Normalization: %d records\n", DATA.size());

	return normalized;
}

/////////////////////////////////////////////////////////////////////////////
int CocoDataset::KEY_COLUMN_ORDINAL()
{
	for(int i=0,L=METADATA.size();i<L;i++)
		if(IS_KEY_COLUMN(METADATA[i]))
			return METADATA[i]->ORDINAL;
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
String CocoDataset::SQL_VALUE(const int& Row, CocoDatasetField* COL)
{
	CocoDatasetRow* RECORD = DATA[Row];

	//------------------------------------------------------------------------------------------
	// We use a variant here to make sure that non-string values are properly formatted
	//------------------------------------------------------------------------------------------
	switch(COL->TYPE)
	{
	case VARTYPE_I1:
	case VARTYPE_I2:
	case VARTYPE_I4:
	case VARTYPE_I8:
	case VARTYPE_UI1:
	case VARTYPE_UI2:
	case VARTYPE_UI4:
	case VARTYPE_UI8:
	case VARTYPE_R4:
	case VARTYPE_R8:
	case VARTYPE_BOOL:
	case VARTYPE_CY:
	case VARTYPE_DECIMAL:
	case VARTYPE_TIMESTAMP:
	case VARTYPE_DATE:
	case VARTYPE_TIME:
	case VARTYPE_DATETIME:

		#if ENABLE_VARIANT
		{
			VARIANT pVal;
			CComBSTR svalue;
			if(COL->DEFAULTVALUE!="" && RECORD->FieldValues[COL->ORDINAL]==NULL_DATA_VALUE)
			{
				svalue = _com_util::ConvertStringToBSTR(DEFAULT(COL->ORDINAL).c_str());
			}
			else
			{
				svalue = _com_util::ConvertStringToBSTR(RECORD->FieldValues[COL->ORDINAL].c_str());
			}
			InitVariantFromString(svalue, &pVal);
			putVariant(RECORD, COL->ORDINAL, pVal, false);
		}
		#endif

		break;
	}
	//------------------------------------------------------------------------------------------

	if(RECORD->FieldValues[COL->ORDINAL]==NULL_DATA_VALUE)
	{
		return String("NULL");
	}
	else
	{
		switch(COL->SQLITE_DATATYPE)
		{
		case SQLITE_INTEGER:
			return RECORD->FieldValues[COL->ORDINAL];

		case SQLITE_FLOAT:
			return RECORD->FieldValues[COL->ORDINAL];

		case SQLITE_BLOB:
			{
				int sz = RECORD->FieldValues[COL->ORDINAL].size();
				String data = ::toBase64((uint8_t*) RECORD->FieldValues[COL->ORDINAL].c_str(), sz);
				return "BASE64_DECODE('" + data + "')";
			}

		case SQLITE_TEXT:
		default:

			switch(COL->TYPE)
			{
			case VARTYPE_I1:
			case VARTYPE_I2:
			case VARTYPE_I4:
			case VARTYPE_I8:
			case VARTYPE_UI1:
			case VARTYPE_UI2:
			case VARTYPE_UI4:
			case VARTYPE_UI8:
			case VARTYPE_R4:
			case VARTYPE_R8:
			case VARTYPE_BOOL:
			case VARTYPE_CY:
			case VARTYPE_DECIMAL:
			case VARTYPE_TIMESTAMP:
				return RECORD->FieldValues[COL->ORDINAL];

			case VARTYPE_DATE:
			case VARTYPE_TIME:
			case VARTYPE_DATETIME:
			case VARTYPE_STRING:
			default:

				std::string value = RECORD->FieldValues[COL->ORDINAL];

				if(value.size()>0)
				{
					size_t start_pos;
					start_pos = 0;
					while((start_pos = value.find('\n', start_pos)) != String::npos)
					{
						value.replace(start_pos, 1, "\\n");
						start_pos += 2;
					}
					start_pos = 0;
					while((start_pos = value.find('\r', start_pos)) != String::npos)
					{
						value.replace(start_pos, 1, "\\r");
						start_pos += 2;
					}
					start_pos = 0;
					while((start_pos = value.find('\t', start_pos)) != String::npos)
					{
						value.replace(start_pos, 1, "\\t");
						start_pos += 2;
					}
					start_pos = 0;
					while((start_pos = value.find('\'', start_pos)) != String::npos)
					{
						value.replace(start_pos, 1, "\'\'");
						start_pos += 2;
					}
				}

				value.insert(value.begin(), '\'');
				value.append("'");

				return String(value);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
String & CocoDataset::BASETABLENAME(const int& Ordinal)
{
	if (Ordinal < 0) return LOCAL_EMPTY_STRING;
	for(int i=0, L=METADATA.size();i<L;i++)
		if(METADATA[i]->ORDINAL==Ordinal)
			return METADATA[i]->BASETABLENAME;
	return LOCAL_EMPTY_STRING;
}

/////////////////////////////////////////////////////////////////////////////
String CocoDataset::NEXT_IDENTITY()
{
	if(m_NEXT_IDENTITY==0)
	{
		m_NEXT_IDENTITY = IDENTITY(BASETABLENAME(KEY_COLUMN_ORDINAL()));
		if(m_NEXT_IDENTITY==0)
			return String("");
	}
	std::ostringstream sid;
	sid << ++m_NEXT_IDENTITY;
	return sid.str();
}

/////////////////////////////////////////////////////////////////////////////
static int sqlite_callback_max_id(void* NotUsed, int argc, char **argv, char **azColName)
{
	int* max_id = (int*)(NotUsed);
	*max_id = argv[0]==NULL ? 0 : atoi(argv[0]);
	return 0;
}

int CocoDataset::IDENTITY(const String& UTF8_tableName)
{
	lastError = "";
	if(UTF8_tableName.size()==0) return -1;
	char* zErrMsg = NULL;
	String tname = UTF8_tableName.substr(1, UTF8_tableName.size()-2);
	String sql("select seq from sqlite_sequence where name='" + tname + "';");
	int max_id = -1;
	int rc = sqlite3_exec(db, sql.c_str(), sqlite_callback_max_id, &max_id, &zErrMsg);
	if(zErrMsg) lastError = String(zErrMsg);
	if(max_id==-1)
	{
		sql = "SELECT MAX(rowid) FROM " + UTF8_tableName;
		zErrMsg = NULL;
		rc = sqlite3_exec(db, sql.c_str(), sqlite_callback_max_id, &max_id, &zErrMsg);
		if(zErrMsg)	lastError = String(zErrMsg);
	}
	return max_id==-1 ? 0 : max_id;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::addIndex(const String& csFieldNames)
{
	needs_reindex = true;
	return INDEX_TABLE.addIndex(csFieldNames);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::removeIndex(const String& indexName)
{
	needs_reindex = true;
	return INDEX_TABLE.removeIndex(indexName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::reindex()
{
	needs_reindex = !INDEX_TABLE.reindex();
	return !needs_reindex;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::search(Array<String>* fieldNames, Array<String>* fieldValues)
{
	return locate(*fieldNames, *fieldValues);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::locate(const String& fieldName, const String& fieldValue)
{
	int R = DATA.size();
	if(!R) return false;

	// Attempt to locate by index
	if(INDEX_TABLE.indexExists(fieldName))
	{
		if(needs_reindex)
		{
			reindex();
		}

		CocoDatasetRow* Record = INDEX_TABLE.locate(fieldName, fieldValue, StatusFilter);
		if(Record)
		{
			__recordIndex = Record->recordIndex;
			return moved();
		}
		return false;
	}

	if(fieldName.indexOf(",")!=-1)
		throw "Invalid Index or Field Name";

	CocoDatasetRow* Record;
	CocoDatasetField* F = this->field(fieldName);
	if(!F) return false;
	int Ordinal = F->ORDINAL;

	// Any chance we are already positioned?
	if(__recordIndex>=0 && __recordIndex<R && DATA[__recordIndex]->FieldValues[Ordinal]==fieldValue)
	{
		Record =  DATA[__recordIndex];
		if(isSet(Record->STATUS, StatusFilter))
			if(Record->FieldValues[Ordinal]==fieldValue)
				return true;
	}

	// Sadly, loop...
	int index = __recordIndex;
	for(int r=0, L=DATA.size(); r<L; r++)
	{
		Record =  DATA[r];
		if(isSet(Record->STATUS, StatusFilter))
		{
			if(Record->FieldValues[Ordinal]==fieldValue)
			{
				__recordIndex = r;
				return moved();
			}
		}
	}

	__recordIndex = index;
	moved();
	return false;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDataset::locate(STRING_LIST& fieldNames, STRING_LIST& fieldValues)
{
	int R = R = DATA.size();
	if(!R) return false;

	// Attempt to locate by index
	static String COMMA(",");

	String indexName = join_vector<String>(fieldNames, COMMA);
	if(INDEX_TABLE.indexExists(indexName))
	{
		if(needs_reindex)
		{
			reindex();
		}

		String ValueKey;
		for(STRING_LIST_ITER i=fieldValues.begin(), E=fieldValues.end(); i!=E; i++)
			ValueKey += "{" + *i + "}";

		CocoDatasetRow* Record = INDEX_TABLE.locate(indexName, ValueKey, StatusFilter);
		if(Record)
		{
			__recordIndex = Record->recordIndex;
			return moved();
		}
		return false;
	}

	int r, f, F = fieldNames.size();
	int match_count = 0;

	std::vector<int> Ordinals;
	for(f=0;f<F;f++)
	{
		CocoDatasetField* FLD =	this->field(fieldNames[f]);
		if(!FLD) return false;
		Ordinals.push_back(FLD->ORDINAL);
	}

	int index = __recordIndex;
	CocoDatasetRow* Record;

	// Any chance we are already positioned?
	if(__recordIndex>=0 && __recordIndex<R)
	{
		Record = DATA[__recordIndex];
		match_count = 0;
		for(f=0; f<F; f++)
		{
			if(isSet(Record->STATUS, StatusFilter))
				if(Record->FieldValues[Ordinals[f]]==fieldValues[f])
					match_count++;
		}
		if(match_count==F)
		{
			return true;
		}
	}

	// Nope, scan the entire dataset
	for(r=0; r<R; r++)
	{
		Record = DATA[r];
		match_count = 0;
		for(f=0; f<F; f++)
		{
			if(isSet(Record->STATUS, StatusFilter))
				if(Record->FieldValues[Ordinals[f]]==fieldValues[f])
					match_count++;
		}
		if(match_count==F)
		{
			__recordIndex = r;
			return moved();
		}
	}

	__recordIndex = index;
	moved();

	return false;
}

/////////////////////////////////////////////////////////////////////////////
String CocoDataset::getBookmark()
{
	String bookmark("");
	if (__recordIndex >= 0 && __recordIndex<(int) DATA.size())
	{
		for(int i=0, L=METADATA.size(); i<L; i++)
			bookmark+="{"+DATA[__recordIndex]->FieldValues[i]+"}";
		bookmark = md5(bookmark);
	}
	return bookmark;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDataset::setBookmark(const String& bookmark)
{
	if(bookmark=="") return false;
	int recordCount = DATA.size();
	int fieldCount = METADATA.size();
	for(int r=0;r<recordCount;r++)
	{
		String bm("");
		for(int c=0;c<fieldCount;c++)
		{
			bm += "{"+DATA[r]->FieldValues[c]+"}";
		}
		if(bookmark == md5(bm))
		{
			return moved();
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::open(const String& base64)
{
	String signature(DATA_STREAM_B64);
	if(base64.find(signature)!=String::npos)
	{
		// Convert Base64 string to bytes
		String data = base64.substr(signature.size());
		std::vector<uint8_t>* bytes = fromBase64(data.c_str());
		bool ret = open((void*) bytes->data(), bytes->size());
		delete bytes;
		return ret;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::open(const void* bytes, const int& size)
{
	close();

	//hexdump((void*)bytes, size);

	int i,recordCount,filedCount;

	CocoDataStream ds;
	ds.write(bytes, size);

	if(ds.readString()=="SQLiteRowset.1")
	{
		fileName = ds.readString();
		SQL = ds.readString();
		ACCESS = (SQLITE_TABLE_ACCESS) ds.readInteger();

		filedCount = ds.readInteger();
		for(i=0; i<filedCount; i++)
		{
			CocoDatasetField* COL = new CocoDatasetField(this);
			COL->read(ds);
			METADATA.push_back(COL);
		}

		recordCount = ds.readInteger();
		for(i=0; i<recordCount; i++)
		{
			CocoDatasetRow* ROW = new CocoDatasetRow(this);
			ROW->read(ds);
			DATA.push_back(ROW);
		}

		moveFirst();
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDataset::toBase64()
{
	UINT size = 0;
	const unsigned char* data = (const unsigned char*) toBytes(size);
	String base64 = DATA_STREAM_B64 + ::toBase64(data, size);
	delete data;
	return base64;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const void* CocoDataset::toBytes(UINT& size)
{
	size=0;

	// We will write metadata and data to this data stream
	int i;
	int filedCount = METADATA.size();
	int recordCount = DATA.size();

	CocoDataStream ds;

	ds.writeString("SQLiteRowset.1");
	ds.writeString(fileName);
	ds.writeString(SQL);
	ds.writeInteger(ACCESS);

	ds.writeInteger(filedCount);
	for(i=0; i<filedCount; i++)
	{
		METADATA[i]->write(ds);
	}

	ds.writeInteger(recordCount);
	for(i=0; i<recordCount; i++)
	{
		DATA[i]->write(ds);
	}

	const void* bytes = ds.read(size);
	//hexdump((void*)bytes, size);

	return bytes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ENABLE_VARIANT
VARIANT CocoDataset::toVariant()
{
	VARIANT out;
	UINT size = 0;
	const void* bytes = toBytes(size);
	InitVariantFromBuffer(bytes, size, &out);
	delete bytes;
	return out;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* CocoDataset::toArrayBuffer()
{
	ArrayBuffer* result = nullptr;
	CocoDataStream* ds = new CocoDataStream;
	if (write(ds))
	{
		result = ds->__get_buffer()->buffer;
	}
	COCO_DELETE_OBJECT(ds);
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Boolean CocoDataset::write(CocoDataStream* ds)
{
	Integer i = 0;
	Integer filedCount = METADATA.size();
	Integer recordCount = DATA.size();
	ds->writeString("SQLiteRowset.1");
	ds->writeString(fileName);
	ds->writeString(SQL);
	ds->writeInteger(static_cast<Integer>(ACCESS));
	ds->writeInteger(filedCount);
	for (i = 0; i < filedCount; i++)
	{
		METADATA[i]->write(*ds);
	}
	ds->writeInteger(recordCount);
	for (i = 0; i < recordCount; i++)
	{
		DATA[i]->write(*ds);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDataset::toJSON()
{
	String s = "";
	Integer fieldCount = METADATA.size();
	Integer recordCount = DATA.size();
	if (fieldCount > 0)
	{
		Integer i = 0;
		Array<String>* t = new Array<String>;
		for (i = 0; i < fieldCount; i++)
		{
			t->push(fieldByIndex(i)->toJSON());
		}
		s = String("{\"METADATA\":[\n") + t->join(",\n") + "],\n\"DATA\":[";
		t->clear();
		for (i = 0; i < recordCount; i++)
		{
			t->push(DATA[i]->toJSON());
		}
		s += String(t->join(",\n")) + "]\n}";
		COCO_DELETE_OBJECT(t);
	}
	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDataset::toDebugString()
{
	String s = "";
	Integer fieldCount = METADATA.size();
	if (fieldCount > 0)
	{
		Array<String>* out = new Array<String>;
		for (Integer i = 0; i < fieldCount; i++)
		{
			s += String(fieldByIndex(i)->NAME) + " | ";
		}
		out->push(s);
		moveFirst();
		while (!DB_EOF)
		{
			s = "";
			for (Integer i = 0; i < fieldCount; i++)
			{
				s += String(fieldByIndex(i)->__get_value()) + " | ";
			}
			out->push(s);
			moveNext();
		}
		s = out->join("\n");
		COCO_DELETE_OBJECT(out);
	}
	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDataset::toXML()
{
	return "";
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDataset::openSchema(String fileName, SQLITE_SCHEMA_ENUM schema)
{
	close();

	if (fileName.charCodeAt(0) == '.')
		fileName = CocoAssetFile::filesPath + fileName.substr(2);

	this->fileName = fileName;

	switch(schema)
	{
	case SQLITE_SCHEMA_ENUM::SQLITE_TABLES:
		{
			exec("SELECT name as [TABLE], sql as [SQL] FROM sqlite_master WHERE type='table';");
			moveFirst();
			sqlite3_close_v2(db);
			ACCESS = (SQLITE_TABLE_ACCESS)(CAN_SELECT);
		}
		return true;

	case SQLITE_SCHEMA_ENUM::SQLITE_VIEWS:
		{
			exec("SELECT name as [VIEW], sql as [SQL] FROM sqlite_master WHERE type='view';");
			moveFirst();
			sqlite3_close_v2(db);
			ACCESS = (SQLITE_TABLE_ACCESS)(CAN_SELECT);
		}
		return true;

	case SQLITE_SCHEMA_ENUM::SQLITE_COLUMNS:
		{
			ADD_META(0, "NAME", VARTYPE_STRING);
			ADD_META(1, "COLUMN", VARTYPE_STRING);
			STRING_LIST TABLES = ENTITIES(fileName, "'table'");
			for(int i=0,L=DATA.size();i<L;i++)
			{
				STRING_LIST COLUMNS = TABLE_COLUMNS(fileName, TABLES[i]);
				for(int j=0,J=COLUMNS.size();j<J; j++)
					ADD_DATA(2, TABLES[i].c_str(), COLUMNS[j].c_str());
			}
			moveFirst();
			sqlite3_close_v2(db);
			ACCESS = (SQLITE_TABLE_ACCESS)(CAN_SELECT);
		}
		return true;

	case SQLITE_SCHEMA_ENUM::SQLITE_FOREIGN_KEYS:
		{
			ADD_META(0, "FK_TABLE", VARTYPE_STRING);
			ADD_META(1, "FK_COLUMN", VARTYPE_STRING);
			ADD_META(2, "PK_TABLE", VARTYPE_STRING);
			ADD_META(3, "PK_COLUMN", VARTYPE_STRING);
			sqlite3* db;
			int rc = sqlite3_open_v2(fileName.c_str(), &db, SQLITE_OPEN_READONLY|SQLITE_OPEN_FULLMUTEX, NULL);
			setLastError();
			if(rc==SQLITE_OK)
			{
				STRING_LIST TABLES = ENTITIES(fileName, "'table'");
				for(int i=0,I=TABLES.size();i<I;i++)
				{
					STRING_LIST COLUMNS = TABLE_COLUMNS(fileName, TABLES[i]);
					for(int j=0,J=COLUMNS.size();j<J; j++)
					{
						CocoDatasetField* COL = new CocoDatasetField(this);
						if(COL->InitColumnMetadata(db, TABLES[i], COLUMNS[j], COLUMNS[j], 0))
						{
							if(COL->SQLITE_PK_TABLE!="" && COL->SQLITE_PK_COLUMN!="")
							{
								ADD_DATA(4, TABLES[i].c_str(), COLUMNS[j].c_str(), COL->SQLITE_PK_TABLE.c_str(), COL->SQLITE_PK_COLUMN.c_str());
							}
						}
						delete COL;
					}
				}
			}
			moveFirst();
			sqlite3_close_v2(db);
			ACCESS = (SQLITE_TABLE_ACCESS)(CAN_SELECT);
		}
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataset::ADD_META(
								uint32_t					ORDINAL,
								String			   			NAME,
								SQLITE_VARTYPE		   		TYPE,
								uint32_t			   		PRECISION,
								uint32_t					SCALE,
								uint32_t					LENGTH,
								SQLITE_COLUMN_FLAGS			FLAGS,
								String			   			BASECOLUMNNAME,
								String			   			BASETABLENAME,
								String						ID,
								uint32_t					LCID,
								uint32_t	    			SIZE,
								String			   			SQLITE_DECLARED_TYPE,
								String			   			SQLITE_PK_COLUMN,
								String			   			SQLITE_PK_TABLE,
								SQLITE_INTERNAL_TYPE		SQLITE_DATATYPE,
								String						DEFAULTVALUE
								)
{
	CocoDatasetField* COL = new CocoDatasetField(this);
	COL->ORDINAL				= ORDINAL;
	COL->ID						= ID;
	COL->NAME					= NAME;
	COL->BASECOLUMNNAME			= BASECOLUMNNAME;
	COL->BASETABLENAME			= BASETABLENAME;
	COL->TYPE					= TYPE;
	COL->LCID					= LCID;
	COL->PRECISION				= PRECISION;
	COL->SCALE					= SCALE;
	COL->SIZE					= SIZE;
	COL->LENGTH					= LENGTH;
	COL->FLAGS					= FLAGS;
	COL->SQLITE_DATATYPE		= SQLITE_DATATYPE;
	COL->SQLITE_DECLARED_TYPE	= SQLITE_DECLARED_TYPE;
	COL->SQLITE_PK_COLUMN		= SQLITE_PK_COLUMN;
	COL->SQLITE_PK_TABLE		= SQLITE_PK_TABLE;
	COL->DEFAULTVALUE			= DEFAULTVALUE;

	METADATA.push_back(COL);
}

/////////////////////////////////////////////////////////////////////////////
void CocoDataset::ADD_DATA(int length, ...)
{
	CocoDatasetRow* ROW = new CocoDatasetRow(this);
	va_list vl;
	va_start(vl,length);
	for(int i=0;i<length;i++)
	{
		ROW->FieldValues[i] = String(va_arg(vl,char*));
	}
	va_end(vl);
	DATA.push_back(ROW);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataset::setLastError()
{
	if(db)
	{
		const char* err = sqlite3_errmsg(db);
		if(err && strcmp(err, "not an error")!=0)
		{
			lastError = String(err)+"";

			int KEY_FIELD_INDEX = KEY_COLUMN_ORDINAL();
			if(KEY_FIELD_INDEX==-1) KEY_FIELD_INDEX = 0;

			debugPrint("\nCSQLiteDataset Error\nFile: %s\nSQL: %s\nError: %s\nKey Field: %s\n",
						fileName.c_str(),
						SQL.c_str(),
						lastError.c_str(),
						(__recordIndex >=0 && __recordIndex<DATA.size() ? DATA[__recordIndex]->FieldValues[KEY_FIELD_INDEX].c_str() : ""));
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDataset::close()
{
	if(db!=NULL)
	{
		sqlite3_close_v2(db);
		db=NULL;
	}

	__recordIndex = -1;
	DB_EOF = false;
	DB_BOF = false;
	m_NEXT_IDENTITY = 0;
	ACCESS = (SQLITE_TABLE_ACCESS)(CAN_SELECT|CAN_INSERT|CAN_DELETE|CAN_UPDATE);

	std::for_each(METADATA.begin(), METADATA.end(), [](CocoDatasetField* field)
	{
		delete field;
	});
	METADATA.clear();

	std::for_each(DATA.begin(), DATA.end(), [](CocoDatasetRow* record)
	{
		delete record;
	});
	DATA.clear();

	INDEX_TABLE.reindex();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int sqlite_callback_entities(void *NotUsed, int argc, char **argv, char **azColName)
{
	STRING_LIST* TABLES = (STRING_LIST*)(NotUsed);
	String TABLE = String::fromUTF8(argv[0]);
	NO_BRACKETS(TABLE);
	TABLES->push_back(TABLE);
	return 0;
}
STRING_LIST CocoDataset::ENTITIES(const String& fileName, const String& types)
{
	lastError = "";
	STRING_LIST TABLES;
	sqlite3* db;
	int rc = sqlite3_open_v2(fileName.c_str(), &db, SQLITE_OPEN_READONLY|SQLITE_OPEN_FULLMUTEX, NULL);
	setLastError();
	if(rc==SQLITE_OK)
	{
		char *zErrMsg = NULL;
		String SQL = "SELECT name as [NAME], sql as [SQL] FROM sqlite_master WHERE type IN (" + types + ");";
		rc = sqlite3_exec(db, SQL.c_str(), sqlite_callback_entities, &TABLES, &zErrMsg);
		if(zErrMsg)	lastError = String(zErrMsg);
	}
	sqlite3_close_v2(db);
	return TABLES;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int sqlite_callback_columns(void *NotUsed, int argc, char **argv, char **azColName)
{
	STRING_LIST* COLUMNS = (STRING_LIST*)(NotUsed);
	String COLUMN = String::fromUTF8(argv[1]);
	NO_BRACKETS(COLUMN);
	COLUMNS->push_back(COLUMN);
	return 0;
}
STRING_LIST CocoDataset::TABLE_COLUMNS(const String& fileName, const String& table)
{
	lastError = "";
	STRING_LIST COLUMNS;
	sqlite3* db;
	int rc = sqlite3_open_v2(fileName.c_str(), &db, SQLITE_OPEN_READONLY|SQLITE_OPEN_FULLMUTEX, NULL);
	setLastError();
	if(rc==SQLITE_OK)
	{
		char *zErrMsg = NULL;
		String SQL("PRAGMA table_info(" + table + ")");
		rc = sqlite3_exec(db, SQL.c_str(), sqlite_callback_columns, &COLUMNS, &zErrMsg);
		if(zErrMsg)	lastError = String(zErrMsg);
	}
	sqlite3_close_v2(db);
	return COLUMNS;
}

// ==================================================================================================================================
//	   ______                 ____        __                  __  ____          __         ______      __    __
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_/  _/___  ____/ /__  _  _/_  __/___ _/ /_  / /__
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __// // __ \/ __  / _ \| |/_// / / __ `/ __ \/ / _ \
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /__/ // / / / /_/ /  __/>  < / / / /_/ / /_/ / /  __/
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/___/_/ /_/\__,_/\___/_/|_|/_/  \__,_/_.___/_/\___/
//
// ==================================================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetIndexTable::CocoDatasetIndexTable(CocoDataset* rowset)
{
	this->rowset = rowset;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetIndexTable::~CocoDatasetIndexTable()
{
	for (std::map<String, CocoDatasetIndex*>::iterator iindex = INDEXES.begin(), E = INDEXES.end(); iindex != E; iindex++)
	{
		CocoDatasetIndex* INDEX = iindex->second;
		delete INDEX;
	}
	INDEXES.clear();
	rowset = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDatasetIndexTable::indexExists(const String& indexName)
{
	std::map<String, CocoDatasetIndex*>::iterator iindex = INDEXES.find(indexName);
	return iindex != INDEXES.end();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDatasetIndexTable::addIndex(String csFieldNames)
{
	CocoDatasetIndex* INDEX = new CocoDatasetIndex(rowset, csFieldNames);
	std::map<String, CocoDatasetIndex*>::iterator iindex = INDEXES.find(INDEX->indexName);
	if (iindex == INDEXES.end())
	{
		INDEXES[INDEX->indexName] = INDEX;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDatasetIndexTable::removeIndex(const String& indexName)
{
	std::map<String, CocoDatasetIndex*>::iterator iindex = INDEXES.find(indexName);
	if (iindex != INDEXES.end())
	{
		CocoDatasetIndex* INDEX = iindex->second;
		INDEXES.erase(iindex);
		delete INDEX;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoDatasetIndexTable::reindex(const String& indexName)
{
	if (indexName)
	{
		std::map<String, CocoDatasetIndex*>::iterator iindex = INDEXES.find(indexName);
		if (iindex != INDEXES.end())
		{
			CocoDatasetIndex* INDEX = iindex->second;
			INDEX->reindex();
			return true;
		}
	}
	else
	{
		int count = 0;
		for (std::map<String, CocoDatasetIndex*>::iterator iindex = INDEXES.begin(), E = INDEXES.end(); iindex != E; iindex++)
		{
			if (iindex->second->reindex())
				count++;
		}
		return (count == INDEXES.size());
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetRow* CocoDatasetIndexTable::locate(const String& fieldName, const String& fieldValue, const SQLITE_RECORD_STATUS& StatusFilter)
{
	String ValueKey = "{" + fieldValue + "}";
	return __locate(fieldName, ValueKey, StatusFilter);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoDatasetRow* CocoDatasetIndexTable::__locate(const String& indexName, const String& ValueKey, const SQLITE_RECORD_STATUS& StatusFilter, ROWSET_DATA* FilteredRecords)
{
	if (FilteredRecords)
		FilteredRecords->clear();

	std::map<String, CocoDatasetIndex*>::iterator iindex = INDEXES.find(indexName);
	if (iindex == INDEXES.end()) return NULL;

	long key = GetCRC((long) ValueKey.c_str(), ValueKey.size());

	std::map<long, ROWSET_DATA>::iterator irecords = iindex->second->RECORDS_PER_FIELD_VALUE.find(key);
	if (irecords == iindex->second->RECORDS_PER_FIELD_VALUE.end()) return NULL;

	ROWSET_DATA* index_records = &(irecords->second);

	for (ROWSET_DATA_ITER irecord = index_records->begin(), E = index_records->end(); irecord != E; irecord++)
	{
		if (isSet((*irecord)->STATUS, StatusFilter))
		{
			if (FilteredRecords)
				FilteredRecords->push_back(*irecord);
			else
				return (*irecord);
		}
	}

	if (FilteredRecords && FilteredRecords->size())
		return (*FilteredRecords)[0];

	return NULL;
}

// ==================================================================================================================================
//	   ______                 ____        __                  __  ____          __
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_/  _/___  ____/ /__  _  __
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __// // __ \/ __  / _ \| |/_/
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /__/ // / / / /_/ /  __/>  <
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/___/_/ /_/\__,_/\___/_/|_|
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////
CocoDatasetIndex::CocoDatasetIndex(CocoDataset* rowset, const String& csFieldNames)
{
	this->rowset = rowset;
	this->indexName = csFieldNames;

	Array<String>* fieldNames = csFieldNames.split(",");

	for (Array<String>::iterator i = fieldNames->begin(), E = fieldNames->end(); i != E; i++)
	{
		CocoDatasetField* F = rowset->field(*i);
		if (F) Ordinals.push_back(F->ORDINAL);
	}

	delete fieldNames;

	m_VALUE_KEY = (char*) malloc(VALUE_KEY_MAX_SIZE);
}

/////////////////////////////////////////////////////////////////////////////
CocoDatasetIndex::~CocoDatasetIndex()
{
	free(m_VALUE_KEY);
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDatasetIndex::reindex()
{
	CocoDatasetRow* record;

	RECORDS_PER_FIELD_VALUE.clear();

	int len = VALUE_KEY_MAX_SIZE;
	int flen = 0;
	long key = 0;

	for (int r = 0, R = rowset->DATA.size(); r<R; r++)
	{
		record = rowset->DATA[r];
		record->recordIndex = r;

		// Construct the ValueKey of this index and get its CRC
		// We use CRC to use numeric comparison in locate instead of string
		memset(m_VALUE_KEY, 0, len);
		len = 0;
		for (int c = 0, C = Ordinals.size(); c<C; c++)
		{
			String & value = record->FieldValues[Ordinals[c]];
			flen = value.size();
			m_VALUE_KEY[len] = '{';
			memcpy(m_VALUE_KEY + len + 1, value.c_str(), flen);
			m_VALUE_KEY[len + flen + 1] = '}';
			len += flen + 2;
		}
		key = GetCRC((long) m_VALUE_KEY, strlen(m_VALUE_KEY));

		// Push record pointer to map vector
		RECORDS_PER_FIELD_VALUE[key].push_back(record);
	}

	return true;
}

// ==================================================================================================================================
//	   ______                 ____        __                  __  ____
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_/ __ \____ _      __
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __/ /_/ / __ \ | /| / /
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /_/ _, _/ /_/ / |/ |/ /
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/_/ |_|\____/|__/|__/
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////
CocoDatasetRow::CocoDatasetRow(CocoDataset* rowset)
{
	this->recordIndex = -1;
	this->dataset = rowset;
	STATUS = SQLITE_RECORD_STATUS::RECORD_UNCHANGED;
	for (int i = 0, L = rowset->METADATA.size(); i < L; i++)
		FieldValues.push_back(NULL_DATA_VALUE);
}

/////////////////////////////////////////////////////////////////////////////
CocoDatasetRow::~CocoDatasetRow()
{
	dataset = NULL;
	FieldValues.clear();
}

/////////////////////////////////////////////////////////////////////////////
CocoDatasetField & CocoDatasetRow::operator [](const int& Ordinal)
{
	CocoDatasetField* field = dataset->EnableMatrixMode ? dataset->field(Ordinal) : dataset->METADATA[Ordinal];
	return *field;
}

/////////////////////////////////////////////////////////////////////////////
CocoDatasetField & CocoDatasetRow::operator [](const String & FieldName)
{
	CocoDatasetField* field = dataset->field(FieldName);
	return *field;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDatasetRow::load(sqlite3_stmt* stmt)
{
	int fieldCount = dataset->METADATA.size();

	for (int ORDINAL = 0; ORDINAL < fieldCount; ORDINAL++)
	{
		// Get uint8_t-length of column
		int length = sqlite3_column_bytes(stmt, ORDINAL);

		// Check for NULL
		if (length == 0 && sqlite3_column_type(stmt, ORDINAL) == SQLITE_NULL)
		{
			FieldValues[ORDINAL] = NULL_DATA_VALUE;
			continue;
		}

		// Get the column metadata
		CocoDatasetField* DATA_COLUMN = dataset->METADATA.at(ORDINAL);

		// Read column data depending on SQLite underlying datatype
		switch (DATA_COLUMN->SQLITE_DATATYPE)
		{
		case SQLITE_INTERNAL_TYPE::SQLITE_VT_INTGER:
		{
			int result = sqlite3_column_int(stmt, ORDINAL);
			char str[30];
			int len = sprintf(str, "%d", result);
			String value(str);
			FieldValues[ORDINAL] = value;
		}
		break;

		case SQLITE_INTERNAL_TYPE::SQLITE_VT_FLOAT:
		{
			double result = sqlite3_column_double(stmt, ORDINAL);
			char str[100];
			int len = sprintf(str, "%g", result);
			String value(str);
			FieldValues[ORDINAL] = value;
		}
		break;

		case SQLITE_INTERNAL_TYPE::SQLITE_VT_BLOB:
		{
			char* result = (char*) sqlite3_column_blob(stmt, ORDINAL);
			if (result)
			{
				String value(result, 0, length);
				FieldValues[ORDINAL] = value;
			}
			else
			{
				FieldValues[ORDINAL] = NULL_DATA_VALUE;
			}
		}
		break;

		case SQLITE_INTERNAL_TYPE::SQLITE_VT_TEXT:
		{
			if (dataset->EnableUTF8)
			{
				// Get UTF8 string
				char* utf8 = (char*) sqlite3_column_text(stmt, ORDINAL);

				// Convert UTF8 to Unicode
				int len = strlen(utf8);
				if (len == 0)
				{
					FieldValues[ORDINAL] = "";
				}
				else
				{
					String value = String::fromUTF8(utf8); // UTF8 to ANSI
					FieldValues[ORDINAL] = value;
				}
			}
			else
			{
				String value((char*) sqlite3_column_text(stmt, ORDINAL));
				FieldValues[ORDINAL] = value;
			}
		}
		break;

		default:
			return false;
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void CocoDatasetRow::write(CocoDataStream& ds)
{
	int fieldCount = dataset->METADATA.size();

	// Write record status
	ds.writeInteger(STATUS);

	// Write values	(special treatment for NULL)
	for (int i = 0; i < fieldCount; i++)
	{
		ds.writeString(FieldValues[i]);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CocoDatasetRow::read(CocoDataStream& ds)
{
	int fieldCount = dataset->METADATA.size();

	// Write record status
	STATUS = (SQLITE_RECORD_STATUS) ds.readInteger();

	// Write values	(special treatment for NULL)
	for (int i = 0; i < fieldCount; i++)
	{
		FieldValues[i] = ds.readString();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDatasetRow::toJSON()
{
	Array<String>* t = new Array<String>;
	Integer fieldCount = dataset->METADATA.size();
	for (Integer i = 0; i < fieldCount; i++)
	{
		t->push(String("\"") + FieldValues[i] + "\"");
	}
	String s = String("{\"STATUS\":") + String(static_cast<Integer>(STATUS)) + ", \"DATA\":[" + t->join(",") + "]}";
	COCO_DELETE_OBJECT(t);
	return s;
}

// ==================================================================================================================================
//	   ______                 ____        __        _______      __    __
//	  / ____/___  _________  / __ \____ _/ /_____ _/ ____(_)__  / /___/ /
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ /_  / / _ \/ / __  /
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ / __/ / /  __/ / /_/ /
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/_/   /_/\___/_/\__,_/
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////
CocoDatasetField::CocoDatasetField(CocoDataset* rowset)
{
	this->dataset = rowset;

	ID = "";
	NAME = "";
	BASECOLUMNNAME = "";
	BASETABLENAME = "";
	SQLITE_DECLARED_TYPE = "";
	SQLITE_PK_COLUMN = "";
	SQLITE_PK_TABLE = "";
	DEFAULTVALUE = "";

	ORDINAL = 0;
	TYPE = SQLITE_VARTYPE::VARTYPE_STRING;
	LCID = 0;
	PRECISION = 0;
	SCALE = 0;
	SIZE = 0;
	LENGTH = 0;
	FLAGS = 0;
	SQLITE_DATATYPE = SQLITE_INTERNAL_TYPE::SQLITE_VT_TEXT;
}

/////////////////////////////////////////////////////////////////////////////
CocoDatasetField::~CocoDatasetField()
{
	dataset = NULL;
}

/////////////////////////////////////////////////////////////////////////////
void CocoDatasetField::copy(CocoDatasetField* col)
{
	dataset = col->dataset;

	ORDINAL = col->ORDINAL;
	ID = col->ID;
	NAME = col->NAME;
	BASECOLUMNNAME = col->BASECOLUMNNAME;
	BASETABLENAME = col->BASETABLENAME;
	TYPE = col->TYPE;
	LCID = col->LCID;
	PRECISION = col->PRECISION;
	SCALE = col->SCALE;
	SIZE = col->SIZE;
	LENGTH = col->LENGTH;
	FLAGS = col->FLAGS;
	SQLITE_DATATYPE = col->SQLITE_DATATYPE;
	SQLITE_DECLARED_TYPE = col->SQLITE_DECLARED_TYPE;
	SQLITE_PK_COLUMN = col->SQLITE_PK_COLUMN;
	SQLITE_PK_TABLE = col->SQLITE_PK_TABLE;
	DEFAULTVALUE = col->DEFAULTVALUE;
}

/////////////////////////////////////////////////////////////////////////////
void CocoDatasetField::write(CocoDataStream& ds)
{
	ds.writeInteger(ORDINAL);
	ds.writeString(ID);
	ds.writeString(NAME);
	ds.writeString(BASECOLUMNNAME);
	ds.writeString(BASETABLENAME);
	ds.writeInteger(TYPE);
	ds.writeInteger(LCID);
	ds.writeInteger(PRECISION);
	ds.writeInteger(SCALE);
	ds.writeInteger(SIZE);
	ds.writeInteger(LENGTH);
	ds.writeInteger(FLAGS);
	ds.writeInteger(SQLITE_DATATYPE);
	ds.writeString(SQLITE_DECLARED_TYPE);
	ds.writeString(SQLITE_PK_COLUMN);
	ds.writeString(SQLITE_PK_TABLE);
	ds.writeString(DEFAULTVALUE);
}

/////////////////////////////////////////////////////////////////////////////
void CocoDatasetField::read(CocoDataStream& ds)
{
	ORDINAL = ds.readInteger();
	ID = ds.readString();
	NAME = ds.readString();
	BASECOLUMNNAME = ds.readString();
	BASETABLENAME = ds.readString();
	TYPE = (SQLITE_VARTYPE) ds.readInteger();
	LCID = ds.readInteger();
	PRECISION = ds.readInteger();
	SCALE = ds.readInteger();
	SIZE = ds.readInteger();
	LENGTH = ds.readInteger();
	FLAGS = ds.readInteger();
	SQLITE_DATATYPE = (SQLITE_INTERNAL_TYPE) ds.readInteger();
	SQLITE_DECLARED_TYPE = ds.readString();
	SQLITE_PK_COLUMN = ds.readString();
	SQLITE_PK_TABLE = ds.readString();
	DEFAULTVALUE = ds.readString();
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDatasetField::InitExpressionColumnMetadata(sqlite3* db, sqlite3_stmt* stmt, const int& Ordinal)
{
	// Set the Ordinal
	ORDINAL = Ordinal;
	FLAGS = IS_COMPUTED;

	#if WIN32_APPLICATION
	LCID = GetSystemDefaultLCID();
	#else
	LCID = 0;
	#endif

	SCALE = 0;

	char cOrdinal[10];
	sprintf(cOrdinal, "%d", Ordinal);
	String sOrdinal(cOrdinal);

	const char* ExprName = sqlite3_column_name(stmt, Ordinal);
	String ColumnName(ExprName ? ExprName : "Expr" + sOrdinal);
	NAME = String::fromUTF8(ColumnName.c_str());
	BASECOLUMNNAME = "[" + String::fromUTF8(ColumnName.c_str()) + "]";
	BASETABLENAME = "[EXPRESSION]";
	ID = BASETABLENAME + "." + BASECOLUMNNAME;

	// Get Data Type
	SQLITE_DATATYPE = (SQLITE_INTERNAL_TYPE) sqlite3_column_type(stmt, 0);
	SQLITE_DECLARED_TYPE = "TEXT";
	switch (SQLITE_DATATYPE)
	{
	case SQLITE_INTEGER: SQLITE_DECLARED_TYPE = "INTEGER"; break;
	case SQLITE_FLOAT:	 SQLITE_DECLARED_TYPE = "FLOAT"; break;
	case SQLITE_BLOB:	 SQLITE_DECLARED_TYPE = "BLOB"; break;
	}

	// Get Extended Datatype Information
	SQLiteColumnMetadata(SQLITE_DECLARED_TYPE);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDatasetField::InitColumnMetadata(sqlite3* db, String UTF8_TableName, String UTF8_ColumnName, String UTF8_AliasColumnName, const int& Ordinal)
{
	// ============================================================================================================================================================
	// Query SQLite database for column metadata
	// ============================================================================================================================================================

	int rc;
	sqlite3_stmt* stmt;

	NO_BRACKETS(UTF8_TableName);
	NO_BRACKETS(UTF8_ColumnName);
	NO_BRACKETS(UTF8_AliasColumnName);

	String SQL("select [" + UTF8_ColumnName + "] from [" + UTF8_TableName + "] where 1=0;");
	rc = sqlite3_prepare_v2(db, SQL.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) return false;

	const char* dt = sqlite3_column_decltype(stmt, 0);
	if (dt == NULL) dt = "INTEGER";

	const char* pzDataType; const char* pzCollSeq; int pNotNull; int pPrimaryKey; int pAutoinc;
	rc = sqlite3_table_column_metadata(db, NULL, sqlite3_column_table_name(stmt, 0), sqlite3_column_origin_name(stmt, 0), &pzDataType, &pzCollSeq, &pNotNull, &pPrimaryKey, &pAutoinc);
	if (rc != SQLITE_OK) return false;

	// ============================================================================================================================================================
	// Set Column Info
	// ============================================================================================================================================================

	ORDINAL = Ordinal;
	NAME = String::fromUTF8(UTF8_AliasColumnName.c_str());										// Get the query name of the column (eg. SELECT [a] AS [b], this holds [b])
	BASECOLUMNNAME = "[" + String::fromUTF8(sqlite3_column_origin_name(stmt, 0)) + "]";				// Get the base name of the column (eg. SELECT [a] AS [b], this holds [a])
	BASETABLENAME = "[" + String::fromUTF8(sqlite3_column_table_name(stmt, 0)) + "]";				// Get the base table name of the column
	ID = BASETABLENAME + "." + BASECOLUMNNAME;
	TYPE = SQLITE_VARTYPE::VARTYPE_STRING;

	#if WIN32_APPLICATION
	LCID = GetSystemDefaultLCID();
	#else
	LCID = 0;
	#endif

	PRECISION = 0;
	SCALE = 0;
	SIZE = 0;
	LENGTH = 0;
	FLAGS = IS_WRITABLE;
	SQLITE_DATATYPE = SQLITE_INTERNAL_TYPE::SQLITE_VT_TEXT;
	SQLITE_DECLARED_TYPE = String::fromUTF8(dt);
	SQLITE_PK_COLUMN = "";
	SQLITE_PK_TABLE = "";
	DEFAULTVALUE = "";

	// ============================================================================================================================================================
	// Set Column Flags
	// ============================================================================================================================================================

	if (pAutoinc != 0)			FLAGS |= (IS_AUTOINCREMENT);
	if (pNotNull == 0)			FLAGS |= (IS_NULLABLE);
	if (pPrimaryKey != 0)		FLAGS |= (IS_KEYCOLUMN | IS_ROWID | IS_UNIQUE);

	// ============================================================================================================================================================
	// Get Extended Datatype Information (scale, precision, length, size)
	// ============================================================================================================================================================

	SQLiteColumnMetadata(SQLITE_DECLARED_TYPE);

	// ============================================================================================================================================================
	// Parse CREATE TABLE SQL for Foreign Key Information
	// ============================================================================================================================================================
	SQL = "SELECT [sql] FROM [sqlite_master] WHERE [tbl_name]='" + UTF8_TableName + "'";
	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);
	rc = sqlite3_prepare_v2(db, SQL.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) return false;

	RegExp m_RegExp;
	for (;;)
	{
		rc = sqlite3_step(stmt);
		char* csql = (char*) sqlite3_column_text(stmt, 0);
		if (csql != NULL)
		{
			String create_sql(csql);
			String pattern(",\\s*(\\w+|(?:\\[[\\w\\s]+\\]))\\s*[^,]*?\\s+REFERENCES\\s+(\\w+|(?:\\[[\\w\\s]+\\]))\\s*\\(\\s*(\\w+|(?:\\[[\\w\\s]+\\]))\\s*\\)");
			int matches = m_RegExp.Parse(create_sql, pattern);
			for (int i = 0; i < matches; i++)
			{
				String col = m_RegExp.SubMatch(i, 0);
				NO_BRACKETS(col);
				if (col == UTF8_ColumnName)
				{
					SQLITE_PK_TABLE = m_RegExp.SubMatch(i, 1);
					SQLITE_PK_COLUMN = m_RegExp.SubMatch(i, 2);
					NO_BRACKETS(SQLITE_PK_TABLE);
					NO_BRACKETS(SQLITE_PK_COLUMN);
				}
			}

			pattern = ",\\s*(\\w+|(?:\\[[\\w\\s]+\\]))\\s*[^,]*?\\s+DEFAULT '([^']*?)'";
			matches = m_RegExp.Parse(create_sql, pattern);
			for (int i = 0; i < matches; i++)
			{
				String col = m_RegExp.SubMatch(i, 0);
				NO_BRACKETS(col);
				if (col == UTF8_ColumnName)
				{
					DEFAULTVALUE = m_RegExp.SubMatch(i, 1);
				}
			}
		}
		if (rc == SQLITE_DONE)
			break;
	}

	// All sqlite chr* will be freed when the statement is freed.
	rc = sqlite3_finalize(stmt);

	ID = Trim(ID);
	NAME = Trim(NAME);
	BASECOLUMNNAME = Trim(BASECOLUMNNAME);
	BASETABLENAME = Trim(BASETABLENAME);
	SQLITE_DECLARED_TYPE = Trim(SQLITE_DECLARED_TYPE);
	SQLITE_PK_COLUMN = Trim(SQLITE_PK_COLUMN);
	SQLITE_PK_TABLE = Trim(SQLITE_PK_TABLE);
	DEFAULTVALUE = Trim(DEFAULTVALUE);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool CocoDatasetField::SQLiteColumnMetadata(String SQLiteDeclaredType)
{
	if (SQLiteDeclaredType.size() == 0)
		return false;

	// -------------------------------------------------------------------------------------------------------------------------
	// Extract precision and scale (eg. DECIMAL(19,2) )
	// -------------------------------------------------------------------------------------------------------------------------

	String DECLARED_TYPE;
	unsigned long DECLARED_SIZE = 0;
	UINT16 DECLARED_PRECISION = 0;
	UINT16 DECLARED_SCALE = 0;

	// We will use a regular expression to extract precision (or size) and scale from the SQLite declared datatype.
	std::transform(SQLiteDeclaredType.begin(), SQLiteDeclaredType.end(), SQLiteDeclaredType.begin(), ::toupper);
	const std::regex pattern("^\\s*(\\w+)(?:\\s*\\(\\s*(\\d+)\\s*(?:,\\s*(\\d+)\\s*)?\\)\\s*)?$");
	const std::sregex_iterator end;
	for (std::sregex_iterator m(SQLiteDeclaredType.cbegin(), SQLiteDeclaredType.cend(), pattern); m != end; ++m)
	{
		DECLARED_TYPE = ((*m)[1]);
		String precision((*m)[2]);
		String scale((*m)[3]);
		DECLARED_SIZE = DECLARED_PRECISION = (precision != "" ? atoi(precision.c_str()) : 0);
		DECLARED_SCALE = scale != "" ? atoi(scale.c_str()) : 0;
	}

	// -------------------------------------------------------------------------------------------------------------------------
	// Map SQLite declared type to DBTYPEENUM
	// -------------------------------------------------------------------------------------------------------------------------
	if (DECLARED_TYPE == "INTEGER")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I4;
	}
	else if (DECLARED_TYPE == "INT1")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I1;
	}
	else if (DECLARED_TYPE == "INT2")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I2;
	}
	else if (DECLARED_TYPE == "INT4")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I4;
	}
	else if (DECLARED_TYPE == "INT8")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I8;
	}
	else if (DECLARED_TYPE == "INT")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I4;
	}
	else if (DECLARED_TYPE == "TINYINT")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I1;
	}
	else if (DECLARED_TYPE == "SMALLINT")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I2;
	}
	else if (DECLARED_TYPE == "MEDIUMINT")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I4;
	}
	else if (DECLARED_TYPE == "BIGINT")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I8;
	}
	else if (DECLARED_TYPE == "LONG")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_I8;
	}

	else if (DECLARED_TYPE == "UNSIGNED BIG INT")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_UI8;
	}
	else if (DECLARED_TYPE == "UINT1")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_UI1;
	}
	else if (DECLARED_TYPE == "UINT2")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_UI2;
	}
	else if (DECLARED_TYPE == "UINT4")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_UI8;
	}
	else if (DECLARED_TYPE == "UINT8")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_UI8;
	}

	else if (DECLARED_TYPE == "REAL")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_R8;
	}
	else if (DECLARED_TYPE == "DOUBLE PRECISION")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_R8;
	}
	else if (DECLARED_TYPE == "DOUBLE")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_R8;
	}
	else if (DECLARED_TYPE == "FLOAT")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_R8;
	}

	else if (DECLARED_TYPE == "BOOLEAN")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BOOL;
	}
	else if (DECLARED_TYPE == "BOOL")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BOOL;
	}

	else if (DECLARED_TYPE == "DATE")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_DATE;
	}
	else if (DECLARED_TYPE == "TIME")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_TIME;
	}
	else if (DECLARED_TYPE == "SMALLDATETIME")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_DATETIME;
	}
	else if (DECLARED_TYPE == "DATETIME")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_DATETIME;
	}
	else if (DECLARED_TYPE == "TIMESTAMP")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_TIMESTAMP;
	}

	else if (DECLARED_TYPE == "SMALLMONEY")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_CY; if (DECLARED_SCALE == 0) DECLARED_SCALE = 2;
	}
	else if (DECLARED_TYPE == "MONEY")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_CY; if (DECLARED_SCALE == 0) DECLARED_SCALE = 2;
	}
	else if (DECLARED_TYPE == "CURRENCY")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_CY; if (DECLARED_SCALE == 0) DECLARED_SCALE = 2;
	}

	else if (DECLARED_TYPE == "IMAGE")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BLOB;
	}
	else if (DECLARED_TYPE == "BLOB")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BLOB;
	}
	else if (DECLARED_TYPE == "BINARY")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BLOB;
	}
	else if (DECLARED_TYPE == "VARBINARY")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BLOB;
	}
	else if (DECLARED_TYPE == "BYTES")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BLOB;
	}
	else if (DECLARED_TYPE == "VARBYTES")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_BLOB;
	}

	else if (DECLARED_TYPE == "DECIMAL")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_DECIMAL;
	}
	else if (DECLARED_TYPE == "NUMERIC")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_DECIMAL;
	}
	else if (DECLARED_TYPE == "NUMBER")	{
		TYPE = SQLITE_VARTYPE::VARTYPE_DECIMAL;
	}

	else
	{
		// All unrecognized declared types fall back to string.
		if (DECLARED_SIZE > 255 || DECLARED_SIZE == 0)
			TYPE = SQLITE_VARTYPE::VARTYPE_STRING;
		else
			TYPE = SQLITE_VARTYPE::VARTYPE_STRING;
	}

	// -------------------------------------------------------------------------------------------------------------------------
	// Set Datatype Size, Scale, Precision
	// -------------------------------------------------------------------------------------------------------------------------

	// Initialize with defaults:

	SIZE = 0;
	PRECISION = 0;
	SCALE = 0;

	// -------------------------------------------------------------------------------------------------------------------------
	// Set fixed size
	// -------------------------------------------------------------------------------------------------------------------------

	if (IsFixedType(TYPE))
		FLAGS |= IS_FIXED_LENGTH;

	switch (TYPE)
	{
		// ======= NUMBERS =====================================================================

	case SQLITE_VARTYPE::VARTYPE_I1:		{ SIZE = sizeof(int8_t);   	LENGTH = 0; PRECISION = 3; 	SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_I2:		{ SIZE = sizeof(int16_t);  	LENGTH = 0; PRECISION = 5; 	SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_I4:		{ SIZE = sizeof(int32_t);  	LENGTH = 0; PRECISION = 10; SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_I8:		{ SIZE = sizeof(int64_t);  	LENGTH = 0; PRECISION = 19; SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_UI1:		{ SIZE = sizeof(uint8_t);  	LENGTH = 0; PRECISION = 3; 	SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_UI2:		{ SIZE = sizeof(uint16_t); 	LENGTH = 0; PRECISION = 5; 	SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_UI4:		{ SIZE = sizeof(uint32_t); 	LENGTH = 0; PRECISION = 10; SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_UI8:		{ SIZE = sizeof(uint64_t); 	LENGTH = 0; PRECISION = 20; SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_R4:		{ SIZE = sizeof(float);  	LENGTH = 0; PRECISION = 7; 	SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }
	case SQLITE_VARTYPE::VARTYPE_R8:		{ SIZE = sizeof(double); 	LENGTH = 0; PRECISION = 16; SCALE = 0; FLAGS |= (IS_SEARCHABLE | IS_SORTABLE); break; }

	case SQLITE_VARTYPE::VARTYPE_CY:
		SIZE = sizeof(CY);
		LENGTH = 0;
		PRECISION = DECLARED_PRECISION ? DECLARED_PRECISION : 19;
		SCALE = DECLARED_SCALE ? DECLARED_SCALE : 8;
		FLAGS |= (IS_SEARCHABLE | IS_SORTABLE);
		break;

	case SQLITE_VARTYPE::VARTYPE_DECIMAL:
		SIZE = sizeof(DECIMAL);
		LENGTH = 0;
		PRECISION = DECLARED_PRECISION ? DECLARED_PRECISION : 28;
		SCALE = DECLARED_SCALE ? DECLARED_SCALE : 4;
		FLAGS |= (IS_SEARCHABLE | IS_SORTABLE);
		break;

	case SQLITE_VARTYPE::VARTYPE_BOOL:
		SIZE = sizeof(VARIANT_BOOL);
		LENGTH = 0;
		PRECISION = 0;
		SCALE = 0;
		FLAGS |= (IS_SEARCHABLE | IS_SORTABLE);
		break;

	// ======= DATES =====================================================================

	case SQLITE_VARTYPE::VARTYPE_DATE:
	case SQLITE_VARTYPE::VARTYPE_DATETIME:
		SIZE = sizeof(DBDATE);
		LENGTH = 0;
		PRECISION = 15;
		SCALE = 0;
		FLAGS |= (IS_SEARCHABLE | IS_SORTABLE);
		break;

	case SQLITE_VARTYPE::VARTYPE_TIME:
		SIZE = sizeof(DBTIME);
		LENGTH = 0;
		PRECISION = 8;
		SCALE = 0;
		FLAGS |= (IS_SEARCHABLE | IS_SORTABLE);
		break;

	case SQLITE_VARTYPE::VARTYPE_TIMESTAMP:
		SIZE = sizeof(DBTIMESTAMP);
		LENGTH = 0;
		PRECISION = 15;
		SCALE = 0;
		FLAGS |= (IS_SEARCHABLE | IS_SORTABLE);
		break;

	// ======= BLOBs =====================================================================
	// Blobs are treated as VARIANT(ARRAY|UI1)

	case SQLITE_VARTYPE::VARTYPE_BLOB:
		SIZE =  ~0;//sizeof(VARIANT);
		LENGTH = 0;
		PRECISION = 0;
		SCALE = 0;
		FLAGS &= ~IS_FIXED_LENGTH;
		break;

	// ======= STRINGS =====================================================================

	case SQLITE_VARTYPE::VARTYPE_STRING:

		if (DECLARED_SIZE == 0)
		{
			// Long Strings

			SIZE = ~0;
			LENGTH = 0;
			FLAGS &= ~IS_FIXED_LENGTH;
			FLAGS &= ~IS_SEARCHABLE;
			FLAGS &= ~IS_SEARCHABLE_LIKE;
			FLAGS &= ~IS_SORTABLE;
		}
		else
		{
			// Fixed-sized Strings

			SIZE = DECLARED_SIZE;
			LENGTH = DECLARED_SIZE;
			FLAGS |= (IS_FIXED_LENGTH | IS_SEARCHABLE | IS_SEARCHABLE_LIKE | IS_SORTABLE);
		}
		break;

	}


	// -------------------------------------------------------------------------------------------------------------------------
	// We need to properly set the generic SQLite type.
	// -------------------------------------------------------------------------------------------------------------------------
	switch (TYPE)
	{
	case SQLITE_VARTYPE::VARTYPE_I1:
	case SQLITE_VARTYPE::VARTYPE_I2:
	case SQLITE_VARTYPE::VARTYPE_I4:
	case SQLITE_VARTYPE::VARTYPE_I8:
	case SQLITE_VARTYPE::VARTYPE_UI1:
	case SQLITE_VARTYPE::VARTYPE_UI2:
	case SQLITE_VARTYPE::VARTYPE_UI4:
	case SQLITE_VARTYPE::VARTYPE_UI8:
	case SQLITE_VARTYPE::VARTYPE_BOOL:

		SQLITE_DATATYPE = SQLITE_INTERNAL_TYPE::SQLITE_VT_INTGER;
		break;

	case SQLITE_VARTYPE::VARTYPE_R4:
	case SQLITE_VARTYPE::VARTYPE_R8:
	case SQLITE_VARTYPE::VARTYPE_CY:
	case SQLITE_VARTYPE::VARTYPE_DECIMAL:

		SQLITE_DATATYPE = SQLITE_INTERNAL_TYPE::SQLITE_VT_FLOAT;
		break;

	case SQLITE_VARTYPE::VARTYPE_BLOB:

		SQLITE_DATATYPE = SQLITE_INTERNAL_TYPE::SQLITE_VT_BLOB;
		break;

	case SQLITE_VARTYPE::VARTYPE_DATE:
	case SQLITE_VARTYPE::VARTYPE_TIME:
	case SQLITE_VARTYPE::VARTYPE_DATETIME:
	case SQLITE_VARTYPE::VARTYPE_TIMESTAMP:
	case SQLITE_VARTYPE::VARTYPE_STRING:
		//case SQLITE_VARTYPE::VARTYPE_WSTR:

		SQLITE_DATATYPE = SQLITE_INTERNAL_TYPE::SQLITE_VT_TEXT;
		break;
	}

	return true;
}

//------------------------------------------------------------------------
// Assignment operator to string
CocoDatasetField::operator String ()
{
	String & v = dataset->EnableMatrixMode ?
		dataset->getValue(dataset->__recordIndex, ORDINAL) :
		dataset->DATA[dataset->__recordIndex]->FieldValues[ORDINAL];
	return v;
}

//------------------------------------------------------------------------
// Assignment operator from field
CocoDatasetField & CocoDatasetField::operator=(const CocoDatasetField & rhs)
{
	// get data from rhs
	const String & v = dataset->EnableMatrixMode ?
		rhs.dataset->getValue(rhs.dataset->__recordIndex, rhs.ORDINAL) :
		rhs.dataset->DATA[rhs.dataset->__recordIndex]->FieldValues[rhs.ORDINAL];

	return operator=(v);
}

//------------------------------------------------------------------------
// Assignment operator from string
CocoDatasetField & CocoDatasetField::operator=(const String& rhs)
{
	// put data on lhs
	if (dataset->EnableMatrixMode)
	{
		dataset->putValue(dataset->__recordIndex, ORDINAL, rhs);
	}
	else
	{
		CocoDatasetRow* Record = dataset->DATA[dataset->__recordIndex];

		if (Record->STATUS != RECORD_DELETED && !(Record->FieldValues[ORDINAL] == rhs))
		{
			Record->FieldValues[ORDINAL] = rhs;

			if (Record->STATUS != RECORD_INSERTED)
				Record->STATUS = RECORD_CHANGED;

			dataset->needs_reindex = true;
		}
	}

	return *this;
}

//------------------------------------------------------------------------
// Equality operator between field and string
bool CocoDatasetField::operator==(const String & rhs)
{
	if (dataset->EnableMatrixMode)
	{
		// lhs value
		String & lhs = dataset->getValue(dataset->__recordIndex, ORDINAL);

		// Use naive string comparison for speed (implemented in String class)
		return (lhs == rhs);
	}
	else
	{
		return dataset->DATA[dataset->__recordIndex]->FieldValues[ORDINAL] == rhs;
	}

	//return (std::strcmp(rhs.c_str(), lhs.c_str())==0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDatasetField::toJSON()
{
	String s = "{";
	s += String("\"ORDINAL\":\"") + String(ORDINAL) + "\"";
	s += String(",\"ID\":\"") + ID + "\"";
	s += String(",\"NAME\":\"") + NAME + "\"";
	s += String(",\"BASECOLUMNNAME\":\"") + BASECOLUMNNAME + "\"";
	s += String(",\"BASETABLENAME\":\"") + BASETABLENAME + "\"";
	s += String(",\"TYPE\":\"") + String(static_cast<Integer>(TYPE)) + "\"";
	s += String(",\"LCID\":\"") + String(LCID) + "\"";
	s += String(",\"PRECISION\":\"") + String(PRECISION) + "\"";
	s += String(",\"SCALE\":\"") + String(SCALE) + "\"";
	s += String(",\"SIZE\":\"") + String(SIZE) + "\"";
	s += String(",\"LENGTH\":\"") + String(LENGTH) + "\"";
	s += String(",\"FLAGS\":\"") + String(static_cast<Integer>(FLAGS)) + "\"";
	s += String(",\"SQLITE_DATATYPE\":\"") + String(static_cast<Integer>(SQLITE_DATATYPE)) + "\"";
	s += String(",\"SQLITE_DECLARED_TYPE\":\"") + SQLITE_DECLARED_TYPE + "\"";
	s += String(",\"SQLITE_PK_COLUMN\":\"") + SQLITE_PK_COLUMN + "\"";
	s += String(",\"SQLITE_PK_TABLE\":\"") + SQLITE_PK_TABLE + "\"";
	s += String(",\"DEFAULTVALUE\":\"") + DEFAULTVALUE + "\"";
	s += "}";
	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoDatasetField::__get_value()
{
	return dataset->getValue(dataset->__recordIndex, ORDINAL);

	/*
	if (dataset->__recordIndex >= 0 && dataset->__recordIndex < (int) dataset->DATA.size() && ORDINAL >= 0 && ORDINAL < (int) dataset->METADATA.size())
	{
		String v = dataset->DATA[dataset->__recordIndex]->FieldValues[ORDINAL];
		if (v == NULL_DATA_VALUE)
		{
			v = dataset->stringForNull;
		}
		return v;
	}
	throw CocoException("Invalid Record");
	*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoDatasetField::__set_value(String v)
{
	dataset->putValue(dataset->__recordIndex, ORDINAL, v);

	/*
	if (dataset->__recordIndex >= 0 && dataset->__recordIndex < (int) dataset->DATA.size() && ORDINAL >= 0 && ORDINAL < (int) dataset->METADATA.size())
	{
		if (v == dataset->stringForNull)
		{
			v = NULL_DATA_VALUE;
		}
		if (dataset->DATA[dataset->__recordIndex]->FieldValues[ORDINAL] != v)
		{
			dataset->DATA[dataset->__recordIndex]->FieldValues[ORDINAL] = v;
			if (dataset->DATA[dataset->__recordIndex]->STATUS != SQLITE_RECORD_STATUS::RECORD_INSERTED)
			{
				dataset->DATA[dataset->__recordIndex]->STATUS = SQLITE_RECORD_STATUS::RECORD_CHANGED;
			}
		}
		return;
	}
	throw CocoException("Invalid Record");
	*/
}

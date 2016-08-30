#ifndef SQLITE_NATIVE_H
#define SQLITE_NATIVE_H

#include "Coconut2D.hpp"
#include "sqlite3.h"

// ==================================================================================================================================
//	    ___    ____  ____     ___        __________  __  ___
//	   /   |  / __ \/ __ \   ( _ )      / ____/ __ \/  |/  /
//	  / /| | / / / / / / /  / __ \/|   / /   / / / / /|_/ /
//	 / ___ |/ /_/ / /_/ /  / /_/  <   / /___/ /_/ / /  / /
//	/_/  |_/_____/\____/   \____/\/   \____/\____/_/  /_/
//
// ==================================================================================================================================

#if ENABLE_VARIANT

	#include <atlbase.h>
	#include <atlcom.h>
	#include <atlcomcli.h>
	#include <atlenc.h>
	#include <comdef.h>
	#include <propvarutil.h>
	#include <Shlobj.h>

	using namespace ATL;

	#pragma comment(lib, "comsvcs.lib")
	#pragma comment(lib, "rpcrt4.lib")
	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "propsys.lib")

	#ifdef SQLITE_COM
	#include "D:/mobileFX/Projects/Software/Coconut/IDE/C++/SQLiteX/SQLiteX_i.h"
	#endif

	#ifdef ENABLE_ADO
	#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
	#endif

	INT VariantToInt(VARIANT& v);
	DOUBLE VariantToDouble(VARIANT& v);
	std::string VariantToString(VARIANT& v);
	SYSTEMTIME VariantToDateTime(VARIANT& v);
	HRESULT extractDate(const WCHAR* p, const WCHAR* *pStopped, SYSTEMTIME &tm);
	HRESULT extractTime(const WCHAR* p, SYSTEMTIME &tm, long &offsetMins);
	HRESULT SystemTimeToVariant(SYSTEMTIME &tm, long offsetMins, VARIANT* dest);
	HRESULT parseDateTime(BSTR charData, VARIANT* dest);
	HRESULT parseDate(BSTR charData, VARIANT * dest);
	HRESULT parseTime(BSTR charData, VARIANT * dest);

#endif

#ifndef MSVC_COMPILER

#ifndef VARIANT_BOOL
	/* 0 == FALSE, -1 == TRUE */
	typedef short VARIANT_BOOL;
#endif

#ifndef DECIMAL
typedef struct tagDEC
{
    unsigned short wReserved;
    union
    {
        struct
        {
            uint8_t scale;
            uint8_t sign;
        };
        unsigned short signscale;
    };
    unsigned long Hi32;
    union
    {
        struct
        {
			#ifdef _MAC
	            unsigned long Mid32;
	            unsigned long Lo32;
			#else
	            unsigned long Lo32;
	            unsigned long Mid32;
			#endif
        };
        uint64_t Lo64;
    };
} DECIMAL;
#endif

#ifndef CY
typedef union tagCY
{
    struct
    {
        unsigned long Lo;
        long Hi;
    } DUMMYSTRUCTNAME;
    int64_t int64;
} CY;
#endif

#endif

#if ANDROID_APPLICATION

typedef struct _SYSTEMTIME
{
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDayOfWeek;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
} SYSTEMTIME;

#endif


// ==================================================================================================================================
//	  ______
//	 /_  __/_  ______  ___  _____
//	  / / / / / / __ \/ _ \/ ___/
//	 / / / /_/ / /_/ /  __(__  )
//	/_/  \__, / .___/\___/____/
//	    /____/_/
// ==================================================================================================================================

// Forward Declarations

#ifdef COCONUT2D_NET
class CocoHttpRequest;
#endif

class CocoDataset;
class CocoDatasetField;
class CocoDatasetRow;
class CocoDatasetIndex;

// Typedefs and Iterators
typedef std::vector<String> STRING_LIST;
typedef STRING_LIST::iterator STRING_LIST_ITER;
typedef std::vector<CocoDatasetField*> ROWSET_META;
typedef std::vector<CocoDatasetRow*> ROWSET_DATA;
typedef ROWSET_DATA::iterator ROWSET_DATA_ITER;
typedef std::map<int, CocoDatasetIndex*>::iterator DATASET_INDEXES_ITER;
typedef std::map<String, ROWSET_DATA>::iterator KEY_RECORDS;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Trim(S) S.trim()
#define debugPrint(S,...)
#define IS_KEY_COLUMN(COL)		(((COL->FLAGS & IS_KEYCOLUMN)==IS_KEYCOLUMN))
#define IS_AUTO_INCREMENT(COL)	(((COL->FLAGS & IS_AUTOINCREMENT)==IS_AUTOINCREMENT))

// ==================================================================================================================================
//	    ____        __          _______
//	   / __ \____ _/ /____     /_  __(_)___ ___  ___
//	  / / / / __ `/ __/ _ \     / / / / __ `__ \/ _ \
//	 / /_/ / /_/ / /_/  __/    / / / / / / / / /  __/
//	/_____/\__,_/\__/\___/    /_/ /_/_/ /_/ /_/\___/
//
// ==================================================================================================================================

typedef struct tagDB_NUMERIC
{
	uint8_t precision;
	uint8_t scale;
	uint8_t sign;
	uint8_t val[ 16 ];
} 	DB_NUMERIC;

typedef struct tagDBDATE
{
	short year;
	unsigned short month;
	unsigned short day;
} 	DBDATE;

typedef struct tagDBTIME
{
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
} 	DBTIME;

typedef struct tagDBTIMESTAMP
{
	short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
	unsigned long fraction;
} DBTIMESTAMP;

// ==================================================================================================================================
//	    ______
//	   / ____/___  __  ______ ___  _____
//	  / __/ / __ \/ / / / __ `__ \/ ___/
//	 / /___/ / / / /_/ / / / / / (__  )
//	/_____/_/ /_/\__,_/_/ /_/ /_/____/
//
// ==================================================================================================================================

#ifndef SQLITE_COM

typedef enum SQLITE_RECORD_STATUS
{
	RECORD_NO_RECORD	= 0,
	RECORD_UNCHANGED	= 1,
	RECORD_CHANGED		= 2,
	RECORD_DELETED		= 4,
	RECORD_INSERTED		= 8,
	RECORD_EDITABLE		= RECORD_UNCHANGED|RECORD_CHANGED|RECORD_INSERTED,
	RECORD_ALL			= RECORD_UNCHANGED|RECORD_CHANGED|RECORD_DELETED|RECORD_INSERTED

} SQLITE_RECORD_STATUS;

typedef enum SQLITE_TABLE_ACCESS
{
	CAN_SELECT		= 0,
	CAN_INSERT		= 1,
	CAN_UPDATE		= 2,
	CAN_DELETE		= 4

} SQLITE_TABLE_ACCESS;

typedef enum SQLITE_COLUMN_FLAGS
{
	IS_UNIQUE			= 0x1,
	IS_KEYCOLUMN		= 0x2,
	IS_SEARCHABLE		= 0x4,
	IS_COMPUTED			= 0x8,
	IS_AUTOINCREMENT	= 0x10,
	IS_SORTABLE			= 0x40,
	IS_WRITABLE			= 0x80,
	IS_SEARCHABLE_LIKE	= 0x200,
	IS_NULLABLE			= 0x400,
	IS_ROWID			= 0x800,
	IS_FIXED_LENGTH		= 0x1000,
	HAS_DEFAULT			= 0x2000,

} SQLITE_COLUMN_FLAGS;

typedef enum SQLITE_SCHEMA_ENUM
{
	SQLITE_TABLES		= 0x1,
	SQLITE_VIEWS		= 0x2,
	SQLITE_COLUMNS		= 0x3,
	SQLITE_FOREIGN_KEYS = 0x4,

} SQLITE_SCHEMA_ENUM;

typedef enum SQLITE_INTERNAL_TYPE
{
	SQLITE_VT_INTGER	= 1,
	SQLITE_VT_FLOAT		= 2,
	SQLITE_VT_TEXT		= 3,
	SQLITE_VT_BLOB		= 4,
	SQLITE_VT_NULL		= 5,

} SQLITE_INTERNAL_TYPE;

typedef enum SQLITE_VARTYPE
{
	VARTYPE_I1			= 16,
	VARTYPE_I2			= 2,
	VARTYPE_I4			= 3,
	VARTYPE_I8			= 20,

	VARTYPE_UI1			= 17,
	VARTYPE_UI2			= 18,
	VARTYPE_UI4			= 19,
	VARTYPE_UI8			= 21,

	VARTYPE_R4			= 4,
	VARTYPE_R8			= 5,

	VARTYPE_BOOL		= 11,

	VARTYPE_DATE		= 133,
	VARTYPE_TIME		= 134,
	VARTYPE_DATETIME	= 7,
	VARTYPE_TIMESTAMP	= 135,

	VARTYPE_CY			= 6,
	VARTYPE_DECIMAL		= 14,

	VARTYPE_BLOB		= 12,

	VARTYPE_STRING		= 8

} SQLITE_VARTYPE;

#endif

// ==================================================================================================================================
//	    ____      ___
//	   /  _/___  / (_)___  ___  _____
//	   / // __ \/ / / __ \/ _ \/ ___/
//	 _/ // / / / / / / / /  __(__  )
//	/___/_/ /_/_/_/_/ /_/\___/____/
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////
inline void NO_BRACKETS(String& v)
{
	String out="";
	for(size_t i=0; i<v.length(); i++)
	{
		if(v.c_str()[i]!='[' && v.c_str()[i]!=']')
			out.push_back(v.c_str()[i]);
	}
	v = out;
}

/////////////////////////////////////////////////////////////////////////////
inline bool IsVariableType(const SQLITE_VARTYPE& wType)
{
	switch(wType)
	{
	case SQLITE_VARTYPE::VARTYPE_STRING:
	case SQLITE_VARTYPE::VARTYPE_BLOB:
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
inline bool IsFixedType(const SQLITE_VARTYPE& wType)
{
	return !IsVariableType(wType);
}

/////////////////////////////////////////////////////////////////////////////
inline bool IsNumericType(const SQLITE_VARTYPE& wType)
{
	switch(wType)
	{
	case SQLITE_VARTYPE::VARTYPE_I1:
	case SQLITE_VARTYPE::VARTYPE_I2:
	case SQLITE_VARTYPE::VARTYPE_I4:
	case SQLITE_VARTYPE::VARTYPE_I8:
	case SQLITE_VARTYPE::VARTYPE_UI1:
	case SQLITE_VARTYPE::VARTYPE_UI2:
	case SQLITE_VARTYPE::VARTYPE_UI4:
	case SQLITE_VARTYPE::VARTYPE_UI8:
	case SQLITE_VARTYPE::VARTYPE_R4:
	case SQLITE_VARTYPE::VARTYPE_R8:
	case SQLITE_VARTYPE::VARTYPE_CY:
	case SQLITE_VARTYPE::VARTYPE_DECIMAL:
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool isSet(const SQLITE_RECORD_STATUS& v, const SQLITE_RECORD_STATUS& flags)
{
	if((flags & SQLITE_RECORD_STATUS::RECORD_CHANGED)==SQLITE_RECORD_STATUS::RECORD_CHANGED)
		if((v & SQLITE_RECORD_STATUS::RECORD_CHANGED)==SQLITE_RECORD_STATUS::RECORD_CHANGED)
			return true;

	if((flags & SQLITE_RECORD_STATUS::RECORD_UNCHANGED)==SQLITE_RECORD_STATUS::RECORD_UNCHANGED)
		if((v & SQLITE_RECORD_STATUS::RECORD_UNCHANGED)==SQLITE_RECORD_STATUS::RECORD_UNCHANGED)
			return true;

	if((flags & SQLITE_RECORD_STATUS::RECORD_INSERTED)==SQLITE_RECORD_STATUS::RECORD_INSERTED)
		if((v & SQLITE_RECORD_STATUS::RECORD_INSERTED)==SQLITE_RECORD_STATUS::RECORD_INSERTED)
			return true;

	if((flags & SQLITE_RECORD_STATUS::RECORD_DELETED)==SQLITE_RECORD_STATUS::RECORD_DELETED)
		if((v & SQLITE_RECORD_STATUS::RECORD_DELETED)==SQLITE_RECORD_STATUS::RECORD_DELETED)
			return true;

	return false;
}

// ==================================================================================================================================
//	    ____        __        _____ __
//	   / __ \____ _/ /_____ _/ ___// /_________  ____ _____ ___
//	  / / / / __ `/ __/ __ `/\__ \/ __/ ___/ _ \/ __ `/ __ `__ \
//	 / /_/ / /_/ / /_/ /_/ /___/ / /_/ /  /  __/ /_/ / / / / / /
//	/_____/\__,_/\__/\__,_//____/\__/_/   \___/\__,_/_/ /_/ /_/
//
// ==================================================================================================================================

class CocoDataStream
{
public:
	const Integer ELEMENTS_INCREMENT = 1024;
	Int32Array* bi;
	Float32Array* bf;
	Integer __offset;
	Integer __length;

	#ifdef COCONUT2D_NET
	CocoHttpRequest* http;
	Boolean openFromURL(String url, Boolean async = false);
	#endif
	Boolean __get_Ready();

	String __className;
	CocoDataStream();
	virtual ~CocoDataStream();
	Boolean openFromArrayBuffer(ArrayBuffer* data);
	Int32Array* __get_buffer();
	void increaseSize(Integer s);
	void shrink();
	Integer __get_offset();
	void __set_offset(Integer v);
	void writeInteger(Integer v);
	void writeFloat(Float v);
	void writeString(String v);
	void writeBoolean(Boolean v);
	void writeInt32Array(Int32Array* v);
	void writeFloat32Array(Float32Array* v);
	void writeDataStream(CocoDataStream* v);
	CocoDataStream* readCocoDataStream();
	void set(Int32Array* v);
	Uint8Array* readUint8Array();
	Int32Array* readInt32Array();
	Float32Array* readFloat32Array();
	Integer readInteger();
	Float readFloat();
	String readString();
	Boolean readBoolean();
	void write(const void* bytes, UINT size);
	void* read(UINT& size);
};

// ==================================================================================================================================
//	   ______                 ____        __                  __  _______      __    __
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_/ ____(_)__  / /___/ /
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __/ /_  / / _ \/ / __  /
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /_/ __/ / /  __/ / /_/ /
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/_/   /_/\___/_/\__,_/
//
// ==================================================================================================================================

class CocoDatasetField
{
public:

	CocoDataset* dataset;

	uint32_t					ORDINAL;
	String		   			NAME;
	String			   		BASECOLUMNNAME;
	String			   		BASETABLENAME;
	String					ID;
	SQLITE_VARTYPE	   		TYPE;
	uint32_t					LCID;
	uint32_t			   		PRECISION;
	uint32_t					SCALE;
	uint32_t	    			SIZE; // in bytes
	uint32_t					LENGTH;
	uint32_t					FLAGS;
	String			   		SQLITE_DECLARED_TYPE;
	String			   		SQLITE_PK_COLUMN;
	String			   		SQLITE_PK_TABLE;
	SQLITE_INTERNAL_TYPE	SQLITE_DATATYPE;
	String					DEFAULTVALUE;

	CocoDatasetField(CocoDataset* rowset);
	~CocoDatasetField();

	void copy(CocoDatasetField* col);
	void write(CocoDataStream& ds);
	void read(CocoDataStream& ds);

	bool InitExpressionColumnMetadata(sqlite3* db, sqlite3_stmt* stmt, const int& Ordinal);
	bool InitColumnMetadata(sqlite3* db, String UTF8_TableName, String UTF8_ColumnName, String UTF8_AliasColumnName, const int& Ordinal);
	bool SQLiteColumnMetadata(String SQLiteDeclaredType);
	String toJSON();

	operator String ();
	CocoDatasetField & operator=(const CocoDatasetField & rhs);
	CocoDatasetField & operator=(const String& rhs);
	bool operator==(const String & rhs);

	String __get_value();
	void __set_value(String value);
};

// ==================================================================================================================================
//	   ______                 ____        __                  __  ____
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_/ __ \____ _      __
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __/ /_/ / __ \ | /| / /
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /_/ _, _/ /_/ / |/ |/ /
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/_/ |_|\____/|__/|__/
//
// ==================================================================================================================================

class CocoDatasetRow
{
public:

	CocoDataset* dataset;

	// reliable only if indexed
	int recordIndex;

	CocoDatasetRow(CocoDataset* rowset);
	~CocoDatasetRow();

	SQLITE_RECORD_STATUS STATUS;
	STRING_LIST FieldValues;

	bool load(sqlite3_stmt* stmt);
	void write(CocoDataStream& ds);
	void read(CocoDataStream& ds);

	String toJSON();

	CocoDatasetField & operator [](const int& Ordinal);
	CocoDatasetField & operator [](const String & FieldName);
};

// ==================================================================================================================================
//	   ______                 ____        __                  __  ____          __
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_/  _/___  ____/ /__  _  __
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __// // __ \/ __  / _ \| |/_/
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /__/ // / / / /_/ /  __/>  <
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/___/_/ /_/\__,_/\___/_/|_|
//
// ==================================================================================================================================

#define VALUE_KEY_MAX_SIZE 2048

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CocoDatasetIndex
{
public:
	CocoDataset* rowset;

	String indexName;
	std::vector<long> Ordinals;
	std::map<long, ROWSET_DATA> RECORDS_PER_FIELD_VALUE;
	char* m_VALUE_KEY;

	CocoDatasetIndex(CocoDataset* rowset, const String& csFieldNames);
	~CocoDatasetIndex();

	bool reindex();
	bool reindex(const int& recordIndex);
	bool reindex(CocoDatasetRow* record);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CocoDatasetIndexTable
{
public:
	CocoDataset* rowset;
	std::map<String, CocoDatasetIndex*> INDEXES;

	CocoDatasetIndexTable(CocoDataset* rowset);
	~CocoDatasetIndexTable();

	bool indexExists(const  String& indexName);
	bool addIndex(String csFieldNames);
	bool removeIndex(const String& indexName);
	bool reindex(const String& indexName="");

	CocoDatasetRow* locate(const String& fieldName, const String& fieldValue, const SQLITE_RECORD_STATUS& StatusFilter);
	CocoDatasetRow* __locate(const String& indexName, const String& ValueKey, const SQLITE_RECORD_STATUS& StatusFilter=RECORD_EDITABLE, ROWSET_DATA* FilteredRecords=NULL);
};

// ==================================================================================================================================
//	   ______                 ____        __                  __
//	  / ____/___  _________  / __ \____ _/ /_____ _________  / /_
//	 / /   / __ \/ ___/ __ \/ / / / __ `/ __/ __ `/ ___/ _ \/ __/
//	/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / /_/ /_/ (__  )  __/ /_
//	\____/\____/\___/\____/_____/\__,_/\__/\__,_/____/\___/\__/
//
// ==================================================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CocoDataset
{
public:

	String name;

	sqlite3* db;
	String fileName;
	String SQL;
	ROWSET_META METADATA;
	ROWSET_DATA DATA;
	CocoDatasetIndexTable INDEX_TABLE;
	SQLITE_TABLE_ACCESS ACCESS;
	int __recordIndex;
	bool DB_EOF;
	bool DB_BOF;

	// Performance Flags
	bool PrimaryKeyIndex;
	bool UpdateInTransaction;
	bool EnableHighPerformance;
	bool RequeryOnUpdate;
	bool EnableUTF8;
	bool EnableMatrixMode;
	String UPDATE_SQL_DIRECTIVE;
	String INSERT_SQL_DIRECTIVE;
	String DELETE_SQL_DIRECTIVE;

	int m_NEXT_IDENTITY;
	String lastError;
	String stringForNull;
	SQLITE_RECORD_STATUS StatusFilter;

	CocoDataset();
	~CocoDataset();

	//------------------------------------------------------------------------
	// SQLite Extensibility to support BLOB as Base64
	static String LOCAL_NULL_DATA_VALUE;
	static void sqlite3_unbase64_fn(sqlite3_context *f, int nargs, sqlite3_value ** args);

	//------------------------------------------------------------------------
	// Open / Query / Requery / Close
	bool openSchema(String fileName, SQLITE_SCHEMA_ENUM schema);
	bool open(const void* bytes, const int& size);
	bool open(String fileName, String SQL);
	bool open(const String& base64);
	bool reopen();
	bool select(const String& SQL);
	bool exec(const String& SQL, const bool& keepDatabaseOpen = false);
	bool requery(const bool& useBookmark=true);
	void close();

	//------------------------------------------------------------------------
	// Async Open
	CocoDataStream* ds;
	bool __get_Ready();

	#ifdef COCONUT2D_NET
	bool openURL(String url, bool sync);
	bool updateURL(String url);
	#endif

	//------------------------------------------------------------------------
	// Indexes
	bool needs_reindex;
	bool addIndex(const String& csFieldNames);
	bool removeIndex(const String& indexName);
	bool reindex();
	bool locate(const String& fieldName, const String& fieldValue);
	bool locate(STRING_LIST& fieldNames, STRING_LIST& fieldValues);
	bool search(Array<String>* fieldNames, Array<String>* fieldValues);

	//------------------------------------------------------------------------
	// Navigation
	bool move(const int& recordIndex);
	bool moveFirst();
	bool moveLast();
	bool moveNext();
	bool movePrev();
	bool moved();

	// Navigation of editable records
	bool first();
	bool next();

	//------------------------------------------------------------------------
	CocoDatasetField & operator ()(const int & Ordinal)
	{
		CocoDatasetField* f = EnableMatrixMode ? field(Ordinal) : METADATA[Ordinal];
		return *f;
	}

	//------------------------------------------------------------------------
	CocoDatasetField & operator ()(const String & FieldName)
	{
		CocoDatasetField* f = field(FieldName);
		return *f;
	}

	//------------------------------------------------------------------------
	CocoDatasetRow & operator [](const int & Row)
	{
		__recordIndex = row_to_record(Row, StatusFilter);
		CocoDatasetRow* record = DATA[__recordIndex];
		return *record;
	}

	//------------------------------------------------------------------------
	// Editing
	SQLITE_RECORD_STATUS status();
	CocoDatasetField* field(const String& name);
	CocoDatasetField* field(const int& ordinal);
	CocoDatasetField* fieldByName(const String& name);
	CocoDatasetField* fieldByIndex(Integer ordinal);
	String & getValue(const int& RecordIndex, const int& Ordinal);
	bool putValue(const int& RecordIndex, const int& Ordinal, const String& value);
	bool insertRecord();
	bool deleteRecord();
	int deleteRecords(const String& FieldName, const String& FieldValue);
	bool update();
	bool update(int& RecordsAffected, int& UpdateErrors);
	bool checkDuplicateIDs(CocoDatasetField* KEY_COLUMN);
	bool normalize();
	bool __internal_update(sqlite3* db, int& RecordsAffected, int& UpdateErrors);
	bool update_step(sqlite3_stmt* stmt, CocoDatasetRow* ROW, int& RecordsAffected, int& UpdateErrors);
	bool update_bind_value(sqlite3_stmt* stmt, CocoDatasetRow* Row, CocoDatasetField* Col, int pIndex);
	void update_sql(std::stringstream& SQL);
	void setLastError();
	bool transactionBegin();
	bool transactionCommit();
	bool transactionRollback(const String& savepointName="");
	bool savepointCreate(const String& name);
	bool savepointRelease(const String& name);
	String getBookmark();
	bool setBookmark(const String& bookmark);
	bool modified();

	//------------------------------------------------------------------------
	// Data binding for Grids
	int recordCount(const SQLITE_RECORD_STATUS& Status = SQLITE_RECORD_STATUS::RECORD_EDITABLE);
	int row_to_record(const int& rowIndex, const SQLITE_RECORD_STATUS& Status = SQLITE_RECORD_STATUS::RECORD_EDITABLE);
	String getMatrix(const int& Row, const int& Col);
	bool putMatrix(const int& Row, const int& Col, const String& value);

	#if ENABLE_VARIANT
	bool open(VARIANT* vBytes);
	VARIANT getVariant(const int& ORDINAL);
	bool putVariant(const int& ORDINAL, VARIANT& newVal, bool AffectStatus = true);
	bool putVariant(CocoDatasetRow* RECORD, const int& ORDINAL, VARIANT& newVal, const bool AffectStatus = true);
	#endif

	//------------------------------------------------------------------------
	// Macros
	int IDENTITY(const String& UTF8_tableName);
	int KEY_COLUMN_ORDINAL();
	String SQL_VALUE(const int& Row, CocoDatasetField* COL);
	String NEXT_IDENTITY();
	String DEFAULT(const int& Ordinal);
	String & BASETABLENAME(const int& Ordinal);
	STRING_LIST TABLE_COLUMNS(const String& fileName, const String& table);
	STRING_LIST ENTITIES(const String& fileName, const String& types);

	void ADD_META(
		uint32_t						ORDINAL,
		String			   			NAME,
		SQLITE_VARTYPE		   		TYPE					= (SQLITE_VARTYPE)VARTYPE_STRING,
		uint32_t			   			PRECISION				= 0,
		uint32_t						SCALE					= 0,
		uint32_t						LENGTH					= 0,
		SQLITE_COLUMN_FLAGS			FLAGS					= (SQLITE_COLUMN_FLAGS)(IS_WRITABLE|IS_NULLABLE|IS_SORTABLE|IS_SEARCHABLE),
		String			   			BASECOLUMNNAME			= "",
		String			   			BASETABLENAME			= "",
		String						ID						= "",
		uint32_t						LCID					= 1032,
		uint32_t	    				SIZE					= 0,
		String			   			SQLITE_DECLARED_TYPE	= "",
		String			   			SQLITE_PK_COLUMN		= "",
		String			   			SQLITE_PK_TABLE			= "",
		SQLITE_INTERNAL_TYPE		SQLITE_DATATYPE			= (SQLITE_INTERNAL_TYPE)SQLITE_VT_TEXT,
		String						DEFAULTVALUE			= ""
		);

	void ADD_DATA(int length, ...);

	//------------------------------------------------------------------------
	// Persistence

	#if ENABLE_VARIANT
	VARIANT toVariant();
	#endif

	String toJSON();
	String toXML();
	const void* toBytes(UINT& size);
	String toBase64();
	String toDebugString();

	ArrayBuffer* toArrayBuffer();
	bool openFromArrayBuffer(ArrayBuffer* ab);

	bool write(CocoDataStream* ds);
	bool openFromDataStream(CocoDataStream* ds);

	// ADO
	bool isADO;
	#ifdef ENABLE_ADO
	bool __ado_openSchema(String fileName, SQLITE_SCHEMA_ENUM schema);
	bool __ado_open(void* bytes, int size);
	bool __ado_open(String fileName, String SQL);
	bool __ado_open(VARIANT* vBytes);
	bool __ado_open(String base64);
	bool __ado_reopen();
	bool __ado_select(String SQL);
	bool __ado_exec(String SQL, bool keepDatabaseOpen = false);
	bool __ado_requery(bool useBookmark=true);
	void __ado_close();
	#endif

};

#endif //SQLITE_NATIVE_H

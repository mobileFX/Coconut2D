# encoding: utf-8

# Pretty-printers for Coconut2D IDE
# Copyright (C) 2016 mobileFX.com
# Based on libstdc++'s pretty printers

import gdb
import re
import sys

############################################################################################################

_have_gdb_printing = True
try:
    import gdb.printing
except ImportError:
    _have_gdb_printing = False

try:
    from gdb.types import get_basic_type
except ImportError:
    # from libstdcxx printers
    def get_basic_type(type):
        # If it points to a reference, get the reference.
        if type.code == gdb.TYPE_CODE_REF:
            type = type.target()

        # Get the unqualified type, stripped of typedefs.
        type = type.unqualified().strip_typedefs()

        return type

from gdb import execute
_have_execute_to_string = True
try:
    s = execute('help', True, True)
    # detect how to invoke ptype
    ptype_cmd = 'ptype/mtr'
    try:
        gdb.execute(ptype_cmd + ' void', True, True)
    except RuntimeError:
        ptype_cmd = 'ptype'
except TypeError:
    _have_execute_to_string = False

try:
    from gdb import parse_and_eval
except ImportError:
    # from http://stackoverflow.com/a/2290941/717706
    def parse_and_eval(exp):
        if gdb.VERSION.startswith("6.8.50.2009"):
            return gdb.parse_and_eval(exp)
        # Work around non-existing gdb.parse_and_eval as in released 7.0
        gdb.execute("set logging redirect on")
        gdb.execute("set logging on")
        gdb.execute("print %s" % exp)
        gdb.execute("set logging off")
        return gdb.history(0)

try:
    class GDB_Value_Wrapper(gdb.Value):
        "Wrapper class for gdb.Value that allows setting extra properties."
        def __init__(self, value):
            super(GDB_Value_Wrapper, self).__init__(value)
            self.__dict__ = {}
except TypeError:
    class GDB_Value_Wrapper():
        "Wrapper class for gdb.Value that allows setting extra properties."
        def __init__(self, value):
            self.gdb_value = value
            self.__dict__ = {}
            self.__dict__['type'] = value.type
            self.__dict__['address'] = value.address
            self.__getitem__ = value.__getitem__

############################################################################################################
class Printer_Gen(object):

    class SubPrinter_Gen(object):
        def match_re(self, v):
            return self.re.search(str(v.basic_type)) != None

        def __init__(self, Printer):
            self.name = Printer.printer_name + '-' + Printer.version
            self.enabled = True
            if hasattr(Printer, 'supports'):
                self.re = None
                self.supports = Printer.supports
            else:
                self.re = re.compile(Printer.type_name_re)
                self.supports = self.match_re
            self.Printer = Printer

        def __call__(self, v):
            if not self.enabled:
                return None
            if self.supports(v):
                v.type_name = str(v.basic_type)
                return self.Printer(v)
            return None

    def __init__(self, name):
        self.name = name
        self.enabled = True
        self.subprinters = []

    def add(self, Printer):
        self.subprinters.append(Printer_Gen.SubPrinter_Gen(Printer))

    def __call__(self, value):
        v = GDB_Value_Wrapper(value)
        v.basic_type = get_basic_type(v.type)
        if not v.basic_type:
            return None
        for subprinter_gen in self.subprinters:
            printer = subprinter_gen(v)
            if printer != None:
                return printer
        return None

############################################################################################################

printer_gen = Printer_Gen('Coconut2D')

############################################################################################################
# This function registers the top-level Printer generator with gdb.
# This should be called from .gdbinit.
def register_printer_gen(obj):
    "Register printer generator with objfile obj."

    global printer_gen

    if _have_gdb_printing:
        gdb.printing.register_pretty_printer(obj, printer_gen, replace=True)
    else:
        if obj is None:
            obj = gdb
        obj.pretty_printers.append(printer_gen)

# Register individual Printer with the top-level Printer generator.
def _register_printer(Printer):
    "Registers a Printer"
    printer_gen.add(Printer)
    return Printer

def _cant_register_printer(Printer):
    print >> sys.stderr, 'Printer [%s] not supported by this gdb version' % Printer.printer_name
    return Printer

def _conditionally_register_printer(condition):
    if condition:
        return _register_printer
    else:
        return _cant_register_printer

###
### Individual Printers follow.
###
### Relevant fields:
###
### - 'printer_name' : Subprinter name used by gdb. (Required.) If it contains
###     regex operators, they must be escaped when refering to it from gdb.
### - 'version' : Appended to the subprinter name. (Required.)
### - 'supports(GDB_Value_Wrapper)' classmethod : If it exists, it is used to
###     determine if the Printer supports the given object.
### - 'type_name_re' : If 'supports(basic_type)' doesn't exist, a default
###     version is used which simply tests whether the type name matches this
###     re. (Either supports() or type_name_re is required.)
### - '__init__' : Its only argument is a GDB_Value_Wrapper.
###

@_register_printer
class CocoString:
    "Pretty Printer for String"
    printer_name = 'String'
    version = '1.0'
    type_name_re = '^String$'

    def __init__(self, value):
        self.typename = value.type_name
        self.value = value

    def to_string(self):
        return self.value['_M_dataplus']['_M_p']

    def display_hint(self):
        return 'string'


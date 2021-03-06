#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
sys.dont_write_bytecode = True

import argparse
parser = argparse.ArgumentParser(description='Description will be here.')
parser.add_argument('-n', '--name', metavar='N', type=str, required=True,
                   help='Subsystem name. Can be ns, acs or uav')
parser.add_argument('-f', '--filename', metavar='F', type=str, required=True,
                   help='file to store results')
args = parser.parse_args()



# C name of array with values in RAM
arr = "gp_val"

SERVO_MIN   = 1000
SERVO_MAX   = 2000

SEND_MIN    = 20
SEND_MAX    = 5000

ONBOARD_PARAM_NAME_LENGTH = 16


# check what we have to use as parameter array
if args.name == "ns":
    import param_table_ns
    param = param_table_ns.param
elif args.name == "acs":
    import param_table_acs
    param = param_table_acs.param
elif args.name == "uav":
    import param_table_uav
    param = param_table_uav.param
else:
    print("wrong name")
    exit(1)


######### checkers ###############
# name lengths
for i in param:
    if len(i[0]) > ONBOARD_PARAM_NAME_LENGTH: # -1 because last char must be 0x00
        print("ERROR: name", '"'+i[0]+'"', "is more than", ONBOARD_PARAM_NAME_LENGTH, "characters")
        exit()

# name duplications
n = 0
while n < len(param):
    p = n + 1
    while p < len(param):
        if param[n][0] == param[p][0]:
            print("ERROR: duplicated parameter names detected")
            print(param[n][0])
            exit()
        p += 1
    n += 1

# values' types
for i in param:
    if i[4] == "u" or i[4] == "i":
        if (type(i[1]) is not int) or (type(i[2]) is not int) or (type(i[3]) is not int):
            print("ERROR: type set to integer but given vales are floats.")
            print(i)
            exit()
    if i[4] == "u" and ((i[1] < 0) or (i[2] < 0) or (i[1] < 0)):
        print("ERROR: type set to unsigned but given values are negative.")
        print(i)
        exit()

    if (i[4] != "u") and (i[4] != "i") and (i[4] != "f"):
        print("ERROR: unsupported type")
        print(i)
        exit()

# boundaries
for i in param:
    if i[5] == "NULL": # for default checker
        if (i[1] <= i[2]) and (i[2] <= i[3]) and (i[1] != i[3]):
            pass
        else:
            print("ERROR: bad boundaries in", i[0])
            exit()
    else: # for different checkers
        if i[1] >= i[3]:
            print("ERROR: bad boundaries in", i[0])
            exit()


# write file
f = open(args.filename, 'w')

# print header
f.write("// This file is automatically generated.\n")
f.write("// Do not edit it!\n")
f.write("// Edit structure definition instead and than rebuild project.\n")
f.write("#define ONBOARD_PARAM_CNT " + str(len(param)) + "\n")
f.write("""
/*
 * volatile array of parameters in RAM
 */
""")
f.write("static param_union_t " + arr + "[ONBOARD_PARAM_CNT] __CCM__;\n")
f.write("""
/**
 *
 */
""")
f.write("const uavparam_t ParamRegistry::param_db[] = {\n")


########### generator #############
n = 0

def getKey(item):
    return item[0]

for i in sorted(param, key=getKey):
    # delete pythonic new line symbols and enclose in quotes text strings
    if i[6] != "NULL":
        helpstr = ""
        for s in i[6]:
            if s != "\n":
                helpstr += s
        helpstr = "\"" + helpstr + "\""
    else:
        helpstr = "NULL"

    # create checker function string
    checker = "PARAM_" + str.upper(i[5])

    # create format string
    if i[4] == "u":
        fmt = "{\"%s\", {.u32 = %u}, {.u32 = %u}, {.u32 = %u}, &%s[%u], %s, MAVLINK_TYPE_UINT32_T, %s},\n"
    elif i[4] == "i":
        fmt = "{\"%s\", {.i32 = %d}, {.i32 = %d}, {.i32 = %d}, &%s[%u], %s, MAVLINK_TYPE_INT32_T,  %s},\n"
    elif i[4] == "f":
        fmt = "{\"%s\", {.f32 = %F}, {.f32 = %F}, {.f32 = %F}, &%s[%u], %s, MAVLINK_TYPE_FLOAT,    %s},\n"
    else:
        f.write("#error \"unsupported type\"\n")
        exit()

    f.write( fmt % (i[0],         i[1],         i[2],        i[3], arr, n,  checker,                  helpstr))
    n += 1

f.write("};\n")

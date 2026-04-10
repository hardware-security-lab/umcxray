#include <stdint.h>
#include <stdio.h>

#include "nvlist_printer.h"

static void
indent_print(int indent)
{
    for (int i = 0; i < indent; i++)
    {
        printf("  ");
    }
}

extern void
print_nvlist(nvlist_t *nvl, int indent)
{
    nvpair_t *pair = NULL;

    for (pair = nvlist_next_nvpair(nvl, NULL); pair != NULL;
         pair = nvlist_next_nvpair(nvl, pair))
    {

        const char *name = nvpair_name(pair);
        data_type_t type = nvpair_type(pair);

        indent_print(indent);
        printf("%s = ", name);

        switch (type)
        {
        case DATA_TYPE_UNKNOWN:
            printf("(unknown)\n");
            break;

        case DATA_TYPE_BOOLEAN:
            printf("true\n");
            break;

        case DATA_TYPE_BYTE:
        {
            uchar_t v;
            if (nvpair_value_byte(pair, &v) == 0)
            {
                printf("0x%x (%u)\n", (unsigned) v, (unsigned) v);
            }
            else
            {
                printf("(error reading byte)\n");
            }
            break;
        }

        case DATA_TYPE_INT16:
        {
            int16_t v;
            if (nvpair_value_int16(pair, &v) == 0)
            {
                printf("%d\n", (int) v);
            }
            else
            {
                printf("(error reading int16)\n");
            }
            break;
        }

        case DATA_TYPE_UINT16:
        {
            uint16_t v;
            if (nvpair_value_uint16(pair, &v) == 0)
            {
                printf("0x%x (%u)\n", (unsigned) v, (unsigned) v);
            }
            else
            {
                printf("(error reading uint16)\n");
            }
            break;
        }

        case DATA_TYPE_INT32:
        {
            int32_t v;
            if (nvpair_value_int32(pair, &v) == 0)
            {
                printf("%d\n", v);
            }
            else
            {
                printf("(error reading int32)\n");
            }
            break;
        }

        case DATA_TYPE_UINT32:
        {
            uint32_t v;
            if (nvpair_value_uint32(pair, &v) == 0)
            {
                printf("0x%x (%u)\n", v, v);
            }
            else
            {
                printf("(error reading uint32)\n");
            }
            break;
        }

        case DATA_TYPE_INT64:
        {
            int64_t v;
            if (nvpair_value_int64(pair, &v) == 0)
            {
                printf("%lld\n", (long long) v);
            }
            else
            {
                printf("(error reading int64)\n");
            }
            break;
        }

        case DATA_TYPE_UINT64:
        {
            uint64_t v;
            if (nvpair_value_uint64(pair, &v) == 0)
            {
                printf("0x%llx (%llu)\n", (unsigned long long) v, (unsigned long long) v);
            }
            else
            {
                printf("(error reading uint64)\n");
            }
            break;
        }

        case DATA_TYPE_STRING:
        {
            char *s;
            if (nvpair_value_string(pair, &s) == 0)
            {
                printf("%s\n", s);
            }
            else
            {
                printf("(error reading string)\n");
            }
            break;
        }

        case DATA_TYPE_BYTE_ARRAY:
        {
            uchar_t *arr;
            uint_t n;
            if (nvpair_value_byte_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("0x%x", (unsigned) arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading byte array)\n");
            }
            break;
        }

        case DATA_TYPE_INT16_ARRAY:
        {
            int16_t *arr;
            uint_t n;
            if (nvpair_value_int16_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("%d", (int) arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading int16 array)\n");
            }
            break;
        }

        case DATA_TYPE_UINT16_ARRAY:
        {
            uint16_t *arr;
            uint_t n;
            if (nvpair_value_uint16_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("0x%x", (unsigned) arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading uint16 array)\n");
            }
            break;
        }

        case DATA_TYPE_INT32_ARRAY:
        {
            int32_t *arr;
            uint_t n;
            if (nvpair_value_int32_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("%d", arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading int32 array)\n");
            }
            break;
        }

        case DATA_TYPE_UINT32_ARRAY:
        {
            uint32_t *arr;
            uint_t n;
            if (nvpair_value_uint32_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("0x%x", arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading uint32 array)\n");
            }
            break;
        }

        case DATA_TYPE_INT64_ARRAY:
        {
            int64_t *arr;
            uint_t n;
            if (nvpair_value_int64_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("%lld", (long long) arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading int64 array)\n");
            }
            break;
        }

        case DATA_TYPE_UINT64_ARRAY:
        {
            uint64_t *arr;
            uint_t n;
            if (nvpair_value_uint64_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("0x%llx", (unsigned long long) arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading uint64 array)\n");
            }
            break;
        }

        case DATA_TYPE_STRING_ARRAY:
        {
            char **arr;
            uint_t n;
            if (nvpair_value_string_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(", ");
                    }
                    printf("\"%s\"", arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading string array)\n");
            }
            break;
        }

        case DATA_TYPE_HRTIME:
        {
            hrtime_t v;
            if (nvpair_value_hrtime(pair, &v) == 0)
            {
                printf("%lld\n", (long long) v);
            }
            else
            {
                printf("(error reading hrtime)\n");
            }
            break;
        }

        case DATA_TYPE_NVLIST:
        {
            nvlist_t *child;
            if (nvpair_value_nvlist(pair, &child) == 0)
            {
                printf("{\n");
                print_nvlist(child, indent + 1);
                indent_print(indent);
                printf("}\n");
            }
            else
            {
                printf("(error reading nvlist)\n");
            }
            break;
        }

        case DATA_TYPE_NVLIST_ARRAY:
        {
            nvlist_t **arr;
            uint_t n;
            if (nvpair_value_nvlist_array(pair, &arr, &n) == 0)
            {
                printf("[\n");
                for (uint_t i = 0; i < n; i++)
                {
                    indent_print(indent + 1);
                    printf("[%u] = {\n", i);
                    print_nvlist(arr[i], indent + 2);
                    indent_print(indent + 1);
                    printf("}\n");
                }
                indent_print(indent);
                printf("]\n");
            }
            else
            {
                printf("(error reading nvlist array)\n");
            }
            break;
        }

        case DATA_TYPE_BOOLEAN_VALUE:
        {
            boolean_t v;
            if (nvpair_value_boolean_value(pair, &v) == 0)
            {
                printf("%s\n", v ? "true" : "false");
            }
            else
            {
                printf("(error reading boolean value)\n");
            }
            break;
        }

        case DATA_TYPE_INT8:
        {
            int8_t v;
            if (nvpair_value_int8(pair, &v) == 0)
            {
                printf("%d\n", (int) v);
            }
            else
            {
                printf("(error reading int8)\n");
            }
            break;
        }

        case DATA_TYPE_UINT8:
        {
            uint8_t v;
            if (nvpair_value_uint8(pair, &v) == 0)
            {
                printf("0x%x (%u)\n", (unsigned) v, (unsigned) v);
            }
            else
            {
                printf("(error reading uint8)\n");
            }
            break;
        }

        case DATA_TYPE_BOOLEAN_ARRAY:
        {
            boolean_t *arr;
            uint_t n;
            if (nvpair_value_boolean_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("%s", arr[i] ? "true" : "false");
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading boolean array)\n");
            }
            break;
        }

        case DATA_TYPE_INT8_ARRAY:
        {
            int8_t *arr;
            uint_t n;
            if (nvpair_value_int8_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("%d", (int) arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading int8 array)\n");
            }
            break;
        }

        case DATA_TYPE_UINT8_ARRAY:
        {
            uint8_t *arr;
            uint_t n;
            if (nvpair_value_uint8_array(pair, &arr, &n) == 0)
            {
                printf("[");
                for (uint_t i = 0; i < n; i++)
                {
                    if (i)
                    {
                        printf(" ");
                    }
                    printf("0x%x", (unsigned) arr[i]);
                }
                printf("]\n");
            }
            else
            {
                printf("(error reading uint8 array)\n");
            }
            break;
        }

        default:
            printf("(unhandled type %d)\n", type);
            break;
        }
    }
}

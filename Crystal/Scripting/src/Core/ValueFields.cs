using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Crystal
{

    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property, Inherited = false, AllowMultiple = false)]
    public abstract class CustomEngineAttribute : Attribute
    {
        public abstract void Process(object value, string variableName, ulong UUID);
    }

    public class ValueField : CustomEngineAttribute // TODO(Jorben): Fix, check last ChatGPT response...
    {
        public override void Process(object value, string variableName, ulong UUID)
        {
            //Console.WriteLine($"Process {value}");

            if (value is byte byteValue) // Equivalent C++ type: uint8_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type byte.");
            }

            else if (value is sbyte sbyteValue) // Equivalent C++ type: int8_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type sbyte.");
            }

            else if (value is short shortValue) // Equivalent C++ type: int16_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type short.");
            }

            else if (value is ushort ushortValue) // Equivalent C++ type: uint16_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type ushort.");
            }

            else if (value is int intValue) // Equivalent C++ type: int32_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type int.");
            }

            else if (value is uint uintValue) // Equivalent C++ type: uint32_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type uint.");
            }

            else if (value is long longValue) // Equivalent C++ type: int64_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type long.");
            }

            else if (value is ulong ulongValue) // Equivalent C++ type: uint64_t
            {
                Console.WriteLine($"Value passed into value field is {value} and type ulong.");
            }

            else if (value is float floatValue) // Equivalent C++ type: float
            {
                Console.WriteLine($"Value passed into value field is {value} and type float.");
            }

            else if (value is double doubleValue) // Equivalent C++ type: double
            {
                Console.WriteLine($"Value passed into value field is {value} and type double.");
            }

            else if (value is char charValue) // Equivalent C++ type: char
            {
                Console.WriteLine($"Value passed into value field is {value} and type char.");
            }

            else if (value is bool boolValue) // Equivalent C++ type: bool
            {
                Console.WriteLine($"Value passed into value field is {value} and type bool.");
            }

            else if (value is string stringValue) // Equivalent C++ type: std::string
            {
                Console.WriteLine($"Value passed into value field is {value} and type string.");
            }

            else
            {
                Console.WriteLine("Value passed into value field is currently not recognized.");
            }

        }
    }
}
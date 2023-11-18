using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Crystal
{

    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property, Inherited = false, AllowMultiple = false)]
    unsafe public abstract class CustomEngineAttribute : Attribute
    {
        unsafe public abstract void Process(object value, string variableName, ulong UUID);
    }

    unsafe public class ValueField : CustomEngineAttribute
    {
        unsafe public override void Process(object value, string variableName, ulong UUID)
        {
            //Console.WriteLine($"Process {value}");
            try
            {
                if (value is byte byteValue) // Equivalent C++ type: uint8_t
                {
                    InternalCalls.ScriptComponent_AddValueField_Byte(UUID, variableName, byteValue);
                }

                else if (value is sbyte sbyteValue) // Equivalent C++ type: int8_t
                {
                    InternalCalls.ScriptComponent_AddValueField_SByte(UUID, variableName, sbyteValue);
                }

                else if (value is short shortValue) // Equivalent C++ type: int16_t
                {
                    InternalCalls.ScriptComponent_AddValueField_Short(UUID, variableName, shortValue);
                }

                else if (value is ushort ushortValue) // Equivalent C++ type: uint16_t
                {
                    InternalCalls.ScriptComponent_AddValueField_UShort(UUID, variableName, ushortValue);
                }

                else if (value is int intValue) // Equivalent C++ type: int32_t
                {
                    InternalCalls.ScriptComponent_AddValueField_Int(UUID, variableName, intValue);
                }

                else if (value is uint uintValue) // Equivalent C++ type: uint32_t
                {
                    InternalCalls.ScriptComponent_AddValueField_UInt(UUID, variableName, uintValue);
                }

                else if (value is long longValue) // Equivalent C++ type: int64_t
                {
                   InternalCalls.ScriptComponent_AddValueField_Long(UUID, variableName, longValue);
                }

                else if (value is ulong ulongValue) // Equivalent C++ type: uint64_t
                {
                    InternalCalls.ScriptComponent_AddValueField_ULong(UUID, variableName, ulongValue);
                }

                else if (value is float floatValue) // Equivalent C++ type: float
                {
                    InternalCalls.ScriptComponent_AddValueField_Float(UUID, variableName, floatValue);
                }

                else if (value is double doubleValue) // Equivalent C++ type: double
                {
                    InternalCalls.ScriptComponent_AddValueField_Double(UUID, variableName, doubleValue);
                }

                else if (value is char charValue) // Equivalent C++ type: char
                {
                    InternalCalls.ScriptComponent_AddValueField_Char(UUID, variableName, charValue);
                }

                else if (value is bool boolValue) // Equivalent C++ type: bool
                {
                    InternalCalls.ScriptComponent_AddValueField_Bool(UUID, variableName, boolValue);
                }

                else if (value is string stringValue) // Equivalent C++ type: std::string
                {
                    InternalCalls.ScriptComponent_AddValueField_String(UUID, variableName, stringValue);
                }

                else
                {
                    //Console.WriteLine("Value passed into value field is currently not recognized.");
                }
            }
            catch (Exception e) 
            {
                Console.WriteLine($"Exception during process of Entity::Init() in C#: {e}");
            }

        }
    }
}
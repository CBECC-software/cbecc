/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OUTPUT_DIAGNOSTICS_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTPUT_DIAGNOSTICS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Output_DiagnosticsExtensibleFields
 *  \brief Enumeration of Output:Diagnostics's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Output_DiagnosticsExtensibleFields, )
#else
class Output_DiagnosticsExtensibleFields: public ::EnumBase<Output_DiagnosticsExtensibleFields> {
 public: 
  enum domain 
  {
Key,   };
  Output_DiagnosticsExtensibleFields()
   : EnumBase<Output_DiagnosticsExtensibleFields>(Key) {} 
  Output_DiagnosticsExtensibleFields(const std::string &t_name) 
   : EnumBase<Output_DiagnosticsExtensibleFields>(t_name) {} 
  Output_DiagnosticsExtensibleFields(int t_value) 
   : EnumBase<Output_DiagnosticsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Output_DiagnosticsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Output_DiagnosticsExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<Output_DiagnosticsExtensibleFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ Output_DiagnosticsExtensibleFields::Key, "Key", "Key"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const Output_DiagnosticsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Output_DiagnosticsExtensibleFields> OptionalOutput_DiagnosticsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTPUT_DIAGNOSTICS_FIELDENUMS_HXX

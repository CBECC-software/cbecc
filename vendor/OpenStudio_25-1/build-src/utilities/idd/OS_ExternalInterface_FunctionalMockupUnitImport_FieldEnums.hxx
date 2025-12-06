/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_EXTERNALINTERFACE_FUNCTIONALMOCKUPUNITIMPORT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_EXTERNALINTERFACE_FUNCTIONALMOCKUPUNITIMPORT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ExternalInterface_FunctionalMockupUnitImportFields
 *  \brief Enumeration of OS:ExternalInterface:FunctionalMockupUnitImport's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ExternalInterface_FunctionalMockupUnitImportFields, )
#else
class OS_ExternalInterface_FunctionalMockupUnitImportFields: public ::EnumBase<OS_ExternalInterface_FunctionalMockupUnitImportFields> {
 public: 
  enum domain 
  {
Handle, Name, FMUFileName, FMUTimeout, FMULoggingOn,   };
  OS_ExternalInterface_FunctionalMockupUnitImportFields()
   : EnumBase<OS_ExternalInterface_FunctionalMockupUnitImportFields>(Handle) {} 
  OS_ExternalInterface_FunctionalMockupUnitImportFields(const std::string &t_name) 
   : EnumBase<OS_ExternalInterface_FunctionalMockupUnitImportFields>(t_name) {} 
  OS_ExternalInterface_FunctionalMockupUnitImportFields(int t_value) 
   : EnumBase<OS_ExternalInterface_FunctionalMockupUnitImportFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ExternalInterface_FunctionalMockupUnitImportFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ExternalInterface_FunctionalMockupUnitImportFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ExternalInterface_FunctionalMockupUnitImportFields>;
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
{ OS_ExternalInterface_FunctionalMockupUnitImportFields::Handle, "Handle", "Handle"},
{ OS_ExternalInterface_FunctionalMockupUnitImportFields::Name, "Name", "Name"},
{ OS_ExternalInterface_FunctionalMockupUnitImportFields::FMUFileName, "FMUFileName", "FMU File Name"},
{ OS_ExternalInterface_FunctionalMockupUnitImportFields::FMUTimeout, "FMUTimeout", "FMU Timeout"},
{ OS_ExternalInterface_FunctionalMockupUnitImportFields::FMULoggingOn, "FMULoggingOn", "FMU LoggingOn"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ExternalInterface_FunctionalMockupUnitImportFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ExternalInterface_FunctionalMockupUnitImportFields> OptionalOS_ExternalInterface_FunctionalMockupUnitImportFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_EXTERNALINTERFACE_FUNCTIONALMOCKUPUNITIMPORT_FIELDENUMS_HXX

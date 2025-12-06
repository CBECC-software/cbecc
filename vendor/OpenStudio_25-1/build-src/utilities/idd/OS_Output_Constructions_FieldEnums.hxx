/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUT_CONSTRUCTIONS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUT_CONSTRUCTIONS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Output_ConstructionsFields
 *  \brief Enumeration of OS:Output:Constructions's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Output_ConstructionsFields, )
#else
class OS_Output_ConstructionsFields: public ::EnumBase<OS_Output_ConstructionsFields> {
 public: 
  enum domain 
  {
Handle, ReportConstructions, ReportMaterials,   };
  OS_Output_ConstructionsFields()
   : EnumBase<OS_Output_ConstructionsFields>(Handle) {} 
  OS_Output_ConstructionsFields(const std::string &t_name) 
   : EnumBase<OS_Output_ConstructionsFields>(t_name) {} 
  OS_Output_ConstructionsFields(int t_value) 
   : EnumBase<OS_Output_ConstructionsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_ConstructionsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_ConstructionsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_ConstructionsFields>;
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
{ OS_Output_ConstructionsFields::Handle, "Handle", "Handle"},
{ OS_Output_ConstructionsFields::ReportConstructions, "ReportConstructions", "Report Constructions"},
{ OS_Output_ConstructionsFields::ReportMaterials, "ReportMaterials", "Report Materials"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_ConstructionsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_ConstructionsFields> OptionalOS_Output_ConstructionsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUT_CONSTRUCTIONS_FIELDENUMS_HXX

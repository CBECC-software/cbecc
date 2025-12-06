/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUTCONTROL_RESILIENCESUMMARIES_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUTCONTROL_RESILIENCESUMMARIES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_OutputControl_ResilienceSummariesFields
 *  \brief Enumeration of OS:OutputControl:ResilienceSummaries's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_OutputControl_ResilienceSummariesFields, )
#else
class OS_OutputControl_ResilienceSummariesFields: public ::EnumBase<OS_OutputControl_ResilienceSummariesFields> {
 public: 
  enum domain 
  {
Handle, HeatIndexAlgorithm,   };
  OS_OutputControl_ResilienceSummariesFields()
   : EnumBase<OS_OutputControl_ResilienceSummariesFields>(Handle) {} 
  OS_OutputControl_ResilienceSummariesFields(const std::string &t_name) 
   : EnumBase<OS_OutputControl_ResilienceSummariesFields>(t_name) {} 
  OS_OutputControl_ResilienceSummariesFields(int t_value) 
   : EnumBase<OS_OutputControl_ResilienceSummariesFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_OutputControl_ResilienceSummariesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_OutputControl_ResilienceSummariesFields>::integer_value()); }
   private:
    friend class EnumBase<OS_OutputControl_ResilienceSummariesFields>;
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
{ OS_OutputControl_ResilienceSummariesFields::Handle, "Handle", "Handle"},
{ OS_OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, "HeatIndexAlgorithm", "Heat Index Algorithm"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_OutputControl_ResilienceSummariesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_OutputControl_ResilienceSummariesFields> OptionalOS_OutputControl_ResilienceSummariesFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUTCONTROL_RESILIENCESUMMARIES_FIELDENUMS_HXX

/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_PERFORMANCEPRECISIONTRADEOFFS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PERFORMANCEPRECISIONTRADEOFFS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PerformancePrecisionTradeoffsFields
 *  \brief Enumeration of OS:PerformancePrecisionTradeoffs's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PerformancePrecisionTradeoffsFields, )
#else
class OS_PerformancePrecisionTradeoffsFields: public ::EnumBase<OS_PerformancePrecisionTradeoffsFields> {
 public: 
  enum domain 
  {
Handle, UseCoilDirectSolutions, ZoneRadiantExchangeAlgorithm, OverrideMode, MaxZoneTempDiff, MaxAllowedDelTemp, UseRepresentativeSurfacesforCalculations,   };
  OS_PerformancePrecisionTradeoffsFields()
   : EnumBase<OS_PerformancePrecisionTradeoffsFields>(Handle) {} 
  OS_PerformancePrecisionTradeoffsFields(const std::string &t_name) 
   : EnumBase<OS_PerformancePrecisionTradeoffsFields>(t_name) {} 
  OS_PerformancePrecisionTradeoffsFields(int t_value) 
   : EnumBase<OS_PerformancePrecisionTradeoffsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PerformancePrecisionTradeoffsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PerformancePrecisionTradeoffsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_PerformancePrecisionTradeoffsFields>;
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
{ OS_PerformancePrecisionTradeoffsFields::Handle, "Handle", "Handle"},
{ OS_PerformancePrecisionTradeoffsFields::UseCoilDirectSolutions, "UseCoilDirectSolutions", "Use Coil Direct Solutions"},
{ OS_PerformancePrecisionTradeoffsFields::ZoneRadiantExchangeAlgorithm, "ZoneRadiantExchangeAlgorithm", "Zone Radiant Exchange Algorithm"},
{ OS_PerformancePrecisionTradeoffsFields::OverrideMode, "OverrideMode", "Override Mode"},
{ OS_PerformancePrecisionTradeoffsFields::MaxZoneTempDiff, "MaxZoneTempDiff", "MaxZoneTempDiff"},
{ OS_PerformancePrecisionTradeoffsFields::MaxAllowedDelTemp, "MaxAllowedDelTemp", "MaxAllowedDelTemp"},
{ OS_PerformancePrecisionTradeoffsFields::UseRepresentativeSurfacesforCalculations, "UseRepresentativeSurfacesforCalculations", "Use Representative Surfaces for Calculations"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PerformancePrecisionTradeoffsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PerformancePrecisionTradeoffsFields> OptionalOS_PerformancePrecisionTradeoffsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PERFORMANCEPRECISIONTRADEOFFS_FIELDENUMS_HXX

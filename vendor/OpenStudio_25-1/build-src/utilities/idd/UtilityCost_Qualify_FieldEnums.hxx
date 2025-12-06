/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_UTILITYCOST_QUALIFY_FIELDENUMS_HXX
#define UTILITIES_IDD_UTILITYCOST_QUALIFY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class UtilityCost_QualifyFields
 *  \brief Enumeration of UtilityCost:Qualify's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(UtilityCost_QualifyFields, )
#else
class UtilityCost_QualifyFields: public ::EnumBase<UtilityCost_QualifyFields> {
 public: 
  enum domain 
  {
UtilityCostQualifyName, TariffName, VariableName, QualifyType, ThresholdValueorVariableName, Season, ThresholdTest, NumberofMonths,   };
  UtilityCost_QualifyFields()
   : EnumBase<UtilityCost_QualifyFields>(UtilityCostQualifyName) {} 
  UtilityCost_QualifyFields(const std::string &t_name) 
   : EnumBase<UtilityCost_QualifyFields>(t_name) {} 
  UtilityCost_QualifyFields(int t_value) 
   : EnumBase<UtilityCost_QualifyFields>(t_value) {} 
  static std::string enumName() 
  { return "UtilityCost_QualifyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UtilityCost_QualifyFields>::integer_value()); }
   private:
    friend class EnumBase<UtilityCost_QualifyFields>;
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
{ UtilityCost_QualifyFields::UtilityCostQualifyName, "UtilityCostQualifyName", "Utility Cost Qualify Name"},
{ UtilityCost_QualifyFields::TariffName, "TariffName", "Tariff Name"},
{ UtilityCost_QualifyFields::VariableName, "VariableName", "Variable Name"},
{ UtilityCost_QualifyFields::QualifyType, "QualifyType", "Qualify Type"},
{ UtilityCost_QualifyFields::ThresholdValueorVariableName, "ThresholdValueorVariableName", "Threshold Value or Variable Name"},
{ UtilityCost_QualifyFields::Season, "Season", "Season"},
{ UtilityCost_QualifyFields::ThresholdTest, "ThresholdTest", "Threshold Test"},
{ UtilityCost_QualifyFields::NumberofMonths, "NumberofMonths", "Number of Months"},
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
  inline std::ostream &operator<<(std::ostream &os, const UtilityCost_QualifyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UtilityCost_QualifyFields> OptionalUtilityCost_QualifyFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_UTILITYCOST_QUALIFY_FIELDENUMS_HXX

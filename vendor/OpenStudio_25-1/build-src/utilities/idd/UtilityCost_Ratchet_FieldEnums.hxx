/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_UTILITYCOST_RATCHET_FIELDENUMS_HXX
#define UTILITIES_IDD_UTILITYCOST_RATCHET_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class UtilityCost_RatchetFields
 *  \brief Enumeration of UtilityCost:Ratchet's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(UtilityCost_RatchetFields, )
#else
class UtilityCost_RatchetFields: public ::EnumBase<UtilityCost_RatchetFields> {
 public: 
  enum domain 
  {
Name, TariffName, BaselineSourceVariable, AdjustmentSourceVariable, SeasonFrom, SeasonTo, MultiplierValueorVariableName, OffsetValueorVariableName,   };
  UtilityCost_RatchetFields()
   : EnumBase<UtilityCost_RatchetFields>(Name) {} 
  UtilityCost_RatchetFields(const std::string &t_name) 
   : EnumBase<UtilityCost_RatchetFields>(t_name) {} 
  UtilityCost_RatchetFields(int t_value) 
   : EnumBase<UtilityCost_RatchetFields>(t_value) {} 
  static std::string enumName() 
  { return "UtilityCost_RatchetFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UtilityCost_RatchetFields>::integer_value()); }
   private:
    friend class EnumBase<UtilityCost_RatchetFields>;
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
{ UtilityCost_RatchetFields::Name, "Name", "Name"},
{ UtilityCost_RatchetFields::TariffName, "TariffName", "Tariff Name"},
{ UtilityCost_RatchetFields::BaselineSourceVariable, "BaselineSourceVariable", "Baseline Source Variable"},
{ UtilityCost_RatchetFields::AdjustmentSourceVariable, "AdjustmentSourceVariable", "Adjustment Source Variable"},
{ UtilityCost_RatchetFields::SeasonFrom, "SeasonFrom", "Season From"},
{ UtilityCost_RatchetFields::SeasonTo, "SeasonTo", "Season To"},
{ UtilityCost_RatchetFields::MultiplierValueorVariableName, "MultiplierValueorVariableName", "Multiplier Value or Variable Name"},
{ UtilityCost_RatchetFields::OffsetValueorVariableName, "OffsetValueorVariableName", "Offset Value or Variable Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const UtilityCost_RatchetFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UtilityCost_RatchetFields> OptionalUtilityCost_RatchetFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_UTILITYCOST_RATCHET_FIELDENUMS_HXX

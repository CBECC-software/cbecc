/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_DISTRICTHEATING_STEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_DISTRICTHEATING_STEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DistrictHeating_SteamFields
 *  \brief Enumeration of DistrictHeating:Steam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DistrictHeating_SteamFields, )
#else
class DistrictHeating_SteamFields: public ::EnumBase<DistrictHeating_SteamFields> {
 public: 
  enum domain 
  {
Name, SteamInletNodeName, SteamOutletNodeName, NominalCapacity, CapacityFractionScheduleName,   };
  DistrictHeating_SteamFields()
   : EnumBase<DistrictHeating_SteamFields>(Name) {} 
  DistrictHeating_SteamFields(const std::string &t_name) 
   : EnumBase<DistrictHeating_SteamFields>(t_name) {} 
  DistrictHeating_SteamFields(int t_value) 
   : EnumBase<DistrictHeating_SteamFields>(t_value) {} 
  static std::string enumName() 
  { return "DistrictHeating_SteamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DistrictHeating_SteamFields>::integer_value()); }
   private:
    friend class EnumBase<DistrictHeating_SteamFields>;
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
{ DistrictHeating_SteamFields::Name, "Name", "Name"},
{ DistrictHeating_SteamFields::SteamInletNodeName, "SteamInletNodeName", "Steam Inlet Node Name"},
{ DistrictHeating_SteamFields::SteamOutletNodeName, "SteamOutletNodeName", "Steam Outlet Node Name"},
{ DistrictHeating_SteamFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ DistrictHeating_SteamFields::CapacityFractionScheduleName, "CapacityFractionScheduleName", "Capacity Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DistrictHeating_SteamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DistrictHeating_SteamFields> OptionalDistrictHeating_SteamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DISTRICTHEATING_STEAM_FIELDENUMS_HXX

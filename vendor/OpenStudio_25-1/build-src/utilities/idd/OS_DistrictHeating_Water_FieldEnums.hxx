/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_DISTRICTHEATING_WATER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_DISTRICTHEATING_WATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_DistrictHeating_WaterFields
 *  \brief Enumeration of OS:DistrictHeating:Water's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_DistrictHeating_WaterFields, )
#else
class OS_DistrictHeating_WaterFields: public ::EnumBase<OS_DistrictHeating_WaterFields> {
 public: 
  enum domain 
  {
Handle, Name, HotWaterInletNodeName, HotWaterOutletNodeName, NominalCapacity, CapacityFractionSchedule,   };
  OS_DistrictHeating_WaterFields()
   : EnumBase<OS_DistrictHeating_WaterFields>(Handle) {} 
  OS_DistrictHeating_WaterFields(const std::string &t_name) 
   : EnumBase<OS_DistrictHeating_WaterFields>(t_name) {} 
  OS_DistrictHeating_WaterFields(int t_value) 
   : EnumBase<OS_DistrictHeating_WaterFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_DistrictHeating_WaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_DistrictHeating_WaterFields>::integer_value()); }
   private:
    friend class EnumBase<OS_DistrictHeating_WaterFields>;
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
{ OS_DistrictHeating_WaterFields::Handle, "Handle", "Handle"},
{ OS_DistrictHeating_WaterFields::Name, "Name", "Name"},
{ OS_DistrictHeating_WaterFields::HotWaterInletNodeName, "HotWaterInletNodeName", "Hot Water Inlet Node Name"},
{ OS_DistrictHeating_WaterFields::HotWaterOutletNodeName, "HotWaterOutletNodeName", "Hot Water Outlet Node Name"},
{ OS_DistrictHeating_WaterFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ OS_DistrictHeating_WaterFields::CapacityFractionSchedule, "CapacityFractionSchedule", "Capacity Fraction Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_DistrictHeating_WaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_DistrictHeating_WaterFields> OptionalOS_DistrictHeating_WaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_DISTRICTHEATING_WATER_FIELDENUMS_HXX

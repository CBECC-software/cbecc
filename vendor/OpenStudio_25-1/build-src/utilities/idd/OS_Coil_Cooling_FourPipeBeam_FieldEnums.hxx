/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_COOLING_FOURPIPEBEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_FOURPIPEBEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_FourPipeBeamFields
 *  \brief Enumeration of OS:Coil:Cooling:FourPipeBeam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_FourPipeBeamFields, )
#else
class OS_Coil_Cooling_FourPipeBeamFields: public ::EnumBase<OS_Coil_Cooling_FourPipeBeamFields> {
 public: 
  enum domain 
  {
Handle, Name, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, BeamRatedCoolingCapacityperBeamLength, BeamRatedCoolingRoomAirChilledWaterTemperatureDifference, BeamRatedChilledWaterVolumeFlowRateperBeamLength, BeamCoolingCapacityTemperatureDifferenceModificationFactorCurveName, BeamCoolingCapacityAirFlowModificationFactorCurveName, BeamCoolingCapacityChilledWaterFlowModificationFactorCurveName,   };
  OS_Coil_Cooling_FourPipeBeamFields()
   : EnumBase<OS_Coil_Cooling_FourPipeBeamFields>(Handle) {} 
  OS_Coil_Cooling_FourPipeBeamFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_FourPipeBeamFields>(t_name) {} 
  OS_Coil_Cooling_FourPipeBeamFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_FourPipeBeamFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_FourPipeBeamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_FourPipeBeamFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_FourPipeBeamFields>;
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
{ OS_Coil_Cooling_FourPipeBeamFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_FourPipeBeamFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_FourPipeBeamFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ OS_Coil_Cooling_FourPipeBeamFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ OS_Coil_Cooling_FourPipeBeamFields::BeamRatedCoolingCapacityperBeamLength, "BeamRatedCoolingCapacityperBeamLength", "Beam Rated Cooling Capacity per Beam Length"},
{ OS_Coil_Cooling_FourPipeBeamFields::BeamRatedCoolingRoomAirChilledWaterTemperatureDifference, "BeamRatedCoolingRoomAirChilledWaterTemperatureDifference", "Beam Rated Cooling Room Air Chilled Water Temperature Difference"},
{ OS_Coil_Cooling_FourPipeBeamFields::BeamRatedChilledWaterVolumeFlowRateperBeamLength, "BeamRatedChilledWaterVolumeFlowRateperBeamLength", "Beam Rated Chilled Water Volume Flow Rate per Beam Length"},
{ OS_Coil_Cooling_FourPipeBeamFields::BeamCoolingCapacityTemperatureDifferenceModificationFactorCurveName, "BeamCoolingCapacityTemperatureDifferenceModificationFactorCurveName", "Beam Cooling Capacity Temperature Difference Modification Factor Curve Name"},
{ OS_Coil_Cooling_FourPipeBeamFields::BeamCoolingCapacityAirFlowModificationFactorCurveName, "BeamCoolingCapacityAirFlowModificationFactorCurveName", "Beam Cooling Capacity Air Flow Modification Factor Curve Name"},
{ OS_Coil_Cooling_FourPipeBeamFields::BeamCoolingCapacityChilledWaterFlowModificationFactorCurveName, "BeamCoolingCapacityChilledWaterFlowModificationFactorCurveName", "Beam Cooling Capacity Chilled Water Flow Modification Factor Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_FourPipeBeamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_FourPipeBeamFields> OptionalOS_Coil_Cooling_FourPipeBeamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_FOURPIPEBEAM_FIELDENUMS_HXX

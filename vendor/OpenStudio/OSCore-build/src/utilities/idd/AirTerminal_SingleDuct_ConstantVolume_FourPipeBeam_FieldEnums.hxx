/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEBEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEBEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields
 *  \brief Enumeration of AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields, )
#else
class AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields: public ::EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields> {
 public: 
  enum domain 
  {
Name, PrimaryAirAvailabilityScheduleName, CoolingAvailabilityScheduleName, HeatingAvailabilityScheduleName, PrimaryAirInletNodeName, PrimaryAirOutletNodeName, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, HotWaterInletNodeName, HotWaterOutletNodeName, DesignPrimaryAirVolumeFlowRate, DesignChilledWaterVolumeFlowRate, DesignHotWaterVolumeFlowRate, ZoneTotalBeamLength, RatedPrimaryAirFlowRateperBeamLength, BeamRatedCoolingCapacityperBeamLength, BeamRatedCoolingRoomAirChilledWaterTemperatureDifference, BeamRatedChilledWaterVolumeFlowRateperBeamLength, BeamCoolingCapacityTemperatureDifferenceModificationFactorCurveName, BeamCoolingCapacityAirFlowModificationFactorCurveName, BeamCoolingCapacityChilledWaterFlowModificationFactorCurveName, BeamRatedHeatingCapacityperBeamLength, BeamRatedHeatingRoomAirHotWaterTemperatureDifference, BeamRatedHotWaterVolumeFlowRateperBeamLength, BeamHeatingCapacityTemperatureDifferenceModificationFactorCurveName, BeamHeatingCapacityAirFlowModificationFactorCurveName, BeamHeatingCapacityHotWaterFlowModificationFactorCurveName,   };
  AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields()
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>(Name) {} 
  AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields(const std::string &t_name) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>(t_name) {} 
  AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields(int t_value) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>(t_value) {} 
  static std::string enumName() 
  { return "AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>::value()); }
   private:
    friend class EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>;
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
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::Name, "Name", "Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName, "PrimaryAirAvailabilityScheduleName", "Primary Air Availability Schedule Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName, "CoolingAvailabilityScheduleName", "Cooling Availability Schedule Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName, "HeatingAvailabilityScheduleName", "Heating Availability Schedule Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirInletNodeName, "PrimaryAirInletNodeName", "Primary Air Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirOutletNodeName, "PrimaryAirOutletNodeName", "Primary Air Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HotWaterInletNodeName, "HotWaterInletNodeName", "Hot Water Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HotWaterOutletNodeName, "HotWaterOutletNodeName", "Hot Water Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, "DesignPrimaryAirVolumeFlowRate", "Design Primary Air Volume Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, "DesignChilledWaterVolumeFlowRate", "Design Chilled Water Volume Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, "DesignHotWaterVolumeFlowRate", "Design Hot Water Volume Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, "ZoneTotalBeamLength", "Zone Total Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, "RatedPrimaryAirFlowRateperBeamLength", "Rated Primary Air Flow Rate per Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamRatedCoolingCapacityperBeamLength, "BeamRatedCoolingCapacityperBeamLength", "Beam Rated Cooling Capacity per Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamRatedCoolingRoomAirChilledWaterTemperatureDifference, "BeamRatedCoolingRoomAirChilledWaterTemperatureDifference", "Beam Rated Cooling Room Air Chilled Water Temperature Difference"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamRatedChilledWaterVolumeFlowRateperBeamLength, "BeamRatedChilledWaterVolumeFlowRateperBeamLength", "Beam Rated Chilled Water Volume Flow Rate per Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamCoolingCapacityTemperatureDifferenceModificationFactorCurveName, "BeamCoolingCapacityTemperatureDifferenceModificationFactorCurveName", "Beam Cooling Capacity Temperature Difference Modification Factor Curve Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamCoolingCapacityAirFlowModificationFactorCurveName, "BeamCoolingCapacityAirFlowModificationFactorCurveName", "Beam Cooling Capacity Air Flow Modification Factor Curve Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamCoolingCapacityChilledWaterFlowModificationFactorCurveName, "BeamCoolingCapacityChilledWaterFlowModificationFactorCurveName", "Beam Cooling Capacity Chilled Water Flow Modification Factor Curve Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamRatedHeatingCapacityperBeamLength, "BeamRatedHeatingCapacityperBeamLength", "Beam Rated Heating Capacity per Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamRatedHeatingRoomAirHotWaterTemperatureDifference, "BeamRatedHeatingRoomAirHotWaterTemperatureDifference", "Beam Rated Heating Room Air Hot Water Temperature Difference"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamRatedHotWaterVolumeFlowRateperBeamLength, "BeamRatedHotWaterVolumeFlowRateperBeamLength", "Beam Rated Hot Water Volume Flow Rate per Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamHeatingCapacityTemperatureDifferenceModificationFactorCurveName, "BeamHeatingCapacityTemperatureDifferenceModificationFactorCurveName", "Beam Heating Capacity Temperature Difference Modification Factor Curve Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamHeatingCapacityAirFlowModificationFactorCurveName, "BeamHeatingCapacityAirFlowModificationFactorCurveName", "Beam Heating Capacity Air Flow Modification Factor Curve Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::BeamHeatingCapacityHotWaterFlowModificationFactorCurveName, "BeamHeatingCapacityHotWaterFlowModificationFactorCurveName", "Beam Heating Capacity Hot Water Flow Modification Factor Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields> OptionalAirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEBEAM_FIELDENUMS_HXX

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

#ifndef UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_COOLEDBEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_COOLEDBEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields
 *  \brief Enumeration of AirTerminal:SingleDuct:ConstantVolume:CooledBeam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields, )
#else
class AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields: public ::EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CooledBeamType, SupplyAirInletNodeName, SupplyAirOutletNodeName, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, SupplyAirVolumetricFlowRate, MaximumTotalChilledWaterVolumetricFlowRate, NumberofBeams, BeamLength, DesignInletWaterTemperature, DesignOutletWaterTemperature, CoilSurfaceAreaperCoilLength, ModelParametera, ModelParametern1, ModelParametern2, ModelParametern3, ModelParametera0, ModelParameterK1, ModelParametern, CoefficientofInductionKin, LeavingPipeInsideDiameter,   };
  AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields()
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>(Name) {} 
  AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields(const std::string &t_name) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>(t_name) {} 
  AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields(int t_value) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>(t_value) {} 
  static std::string enumName() 
  { return "AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>::value()); }
   private:
    friend class EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>;
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
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::Name, "Name", "Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType, "CooledBeamType", "Cooled Beam Type"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirInletNodeName, "SupplyAirInletNodeName", "Supply Air Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirOutletNodeName, "SupplyAirOutletNodeName", "Supply Air Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, "SupplyAirVolumetricFlowRate", "Supply Air Volumetric Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, "MaximumTotalChilledWaterVolumetricFlowRate", "Maximum Total Chilled Water Volumetric Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, "NumberofBeams", "Number of Beams"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, "BeamLength", "Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature, "DesignInletWaterTemperature", "Design Inlet Water Temperature"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature, "DesignOutletWaterTemperature", "Design Outlet Water Temperature"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoilSurfaceAreaperCoilLength, "CoilSurfaceAreaperCoilLength", "Coil Surface Area per Coil Length"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametera, "ModelParametera", "Model Parameter a"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern1, "ModelParametern1", "Model Parameter n1"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern2, "ModelParametern2", "Model Parameter n2"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern3, "ModelParametern3", "Model Parameter n3"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametera0, "ModelParametera0", "Model Parameter a0"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParameterK1, "ModelParameterK1", "Model Parameter K1"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern, "ModelParametern", "Model Parameter n"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, "CoefficientofInductionKin", "Coefficient of Induction Kin"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::LeavingPipeInsideDiameter, "LeavingPipeInsideDiameter", "Leaving Pipe Inside Diameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields> OptionalAirTerminal_SingleDuct_ConstantVolume_CooledBeamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_COOLEDBEAM_FIELDENUMS_HXX

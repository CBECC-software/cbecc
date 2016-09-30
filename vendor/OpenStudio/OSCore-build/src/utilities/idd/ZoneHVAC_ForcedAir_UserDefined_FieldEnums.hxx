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

#ifndef UTILITIES_IDD_ZONEHVAC_FORCEDAIR_USERDEFINED_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_FORCEDAIR_USERDEFINED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_ForcedAir_UserDefinedFields
 *  \brief Enumeration of ZoneHVAC:ForcedAir:UserDefined's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_ForcedAir_UserDefinedFields, )
#else
class ZoneHVAC_ForcedAir_UserDefinedFields: public ::EnumBase<ZoneHVAC_ForcedAir_UserDefinedFields> {
 public: 
  enum domain 
  {
Name, OverallModelSimulationProgramCallingManagerName, ModelSetupandSizingProgramCallingManagerName, PrimaryAirInletNodeName, PrimaryAirOutletNodeName, SecondaryAirInletNodeName, SecondaryAirOutletNodeName, NumberofPlantLoopConnections, PlantConnection1InletNodeName, PlantConnection1OutletNodeName, PlantConnection2InletNodeName, PlantConnection2OutletNodeName, PlantConnection3InletNodeName, PlantConnection3OutletNodeName, SupplyInletWaterStorageTankName, CollectionOutletWaterStorageTankName, AmbientZoneName,   };
  ZoneHVAC_ForcedAir_UserDefinedFields()
   : EnumBase<ZoneHVAC_ForcedAir_UserDefinedFields>(Name) {} 
  ZoneHVAC_ForcedAir_UserDefinedFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_ForcedAir_UserDefinedFields>(t_name) {} 
  ZoneHVAC_ForcedAir_UserDefinedFields(int t_value) 
   : EnumBase<ZoneHVAC_ForcedAir_UserDefinedFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_ForcedAir_UserDefinedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_ForcedAir_UserDefinedFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_ForcedAir_UserDefinedFields>;
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
{ ZoneHVAC_ForcedAir_UserDefinedFields::Name, "Name", "Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::OverallModelSimulationProgramCallingManagerName, "OverallModelSimulationProgramCallingManagerName", "Overall Model Simulation Program Calling Manager Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::ModelSetupandSizingProgramCallingManagerName, "ModelSetupandSizingProgramCallingManagerName", "Model Setup and Sizing Program Calling Manager Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PrimaryAirInletNodeName, "PrimaryAirInletNodeName", "Primary Air Inlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PrimaryAirOutletNodeName, "PrimaryAirOutletNodeName", "Primary Air Outlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::SecondaryAirInletNodeName, "SecondaryAirInletNodeName", "Secondary Air Inlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::SecondaryAirOutletNodeName, "SecondaryAirOutletNodeName", "Secondary Air Outlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::NumberofPlantLoopConnections, "NumberofPlantLoopConnections", "Number of Plant Loop Connections"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PlantConnection1InletNodeName, "PlantConnection1InletNodeName", "Plant Connection 1 Inlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PlantConnection1OutletNodeName, "PlantConnection1OutletNodeName", "Plant Connection 1 Outlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PlantConnection2InletNodeName, "PlantConnection2InletNodeName", "Plant Connection 2 Inlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PlantConnection2OutletNodeName, "PlantConnection2OutletNodeName", "Plant Connection 2 Outlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PlantConnection3InletNodeName, "PlantConnection3InletNodeName", "Plant Connection 3 Inlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::PlantConnection3OutletNodeName, "PlantConnection3OutletNodeName", "Plant Connection 3 Outlet Node Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::SupplyInletWaterStorageTankName, "SupplyInletWaterStorageTankName", "Supply Inlet Water Storage Tank Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::CollectionOutletWaterStorageTankName, "CollectionOutletWaterStorageTankName", "Collection Outlet Water Storage Tank Name"},
{ ZoneHVAC_ForcedAir_UserDefinedFields::AmbientZoneName, "AmbientZoneName", "Ambient Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_ForcedAir_UserDefinedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_ForcedAir_UserDefinedFields> OptionalZoneHVAC_ForcedAir_UserDefinedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_FORCEDAIR_USERDEFINED_FIELDENUMS_HXX

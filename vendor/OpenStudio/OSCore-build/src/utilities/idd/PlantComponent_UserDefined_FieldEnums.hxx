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

#ifndef UTILITIES_IDD_PLANTCOMPONENT_USERDEFINED_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTCOMPONENT_USERDEFINED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantComponent_UserDefinedFields
 *  \brief Enumeration of PlantComponent:UserDefined's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantComponent_UserDefinedFields, )
#else
class PlantComponent_UserDefinedFields: public ::EnumBase<PlantComponent_UserDefinedFields> {
 public: 
  enum domain 
  {
Name, MainModelProgramCallingManagerName, NumberofPlantLoopConnections, PlantConnection1InletNodeName, PlantConnection1OutletNodeName, PlantConnection1LoadingMode, PlantConnection1LoopFlowRequestMode, PlantConnection1InitializationProgramCallingManagerName, PlantConnection1SimulationProgramCallingManagerName, PlantConnection2InletNodeName, PlantConnection2OutletNodeName, PlantConnection2LoadingMode, PlantConnection2LoopFlowRequestMode, PlantConnection2InitializationProgramCallingManagerName, PlantConnection2SimulationProgramCallingManagerName, PlantConnection3InletNodeName, PlantConnection3OutletNodeName, PlantConnection3LoadingMode, PlantConnection3LoopFlowRequestMode, PlantConnection3InitializationProgramCallingManagerName, PlantConnection3SimulationProgramCallingManagerName, PlantConnection4InletNodeName, PlantConnection4OutletNodeName, PlantConnection4LoadingMode, PlantConnection4LoopFlowRequestMode, PlantConnection4InitializationProgramCallingManagerName, PlantConnection4SimulationProgramCallingManagerName, AirConnectionInletNodeName, AirConnectionOutletNodeName, SupplyInletWaterStorageTankName, CollectionOutletWaterStorageTankName, AmbientZoneName,   };
  PlantComponent_UserDefinedFields()
   : EnumBase<PlantComponent_UserDefinedFields>(Name) {} 
  PlantComponent_UserDefinedFields(const std::string &t_name) 
   : EnumBase<PlantComponent_UserDefinedFields>(t_name) {} 
  PlantComponent_UserDefinedFields(int t_value) 
   : EnumBase<PlantComponent_UserDefinedFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantComponent_UserDefinedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantComponent_UserDefinedFields>::value()); }
   private:
    friend class EnumBase<PlantComponent_UserDefinedFields>;
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
{ PlantComponent_UserDefinedFields::Name, "Name", "Name"},
{ PlantComponent_UserDefinedFields::MainModelProgramCallingManagerName, "MainModelProgramCallingManagerName", "Main Model Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::NumberofPlantLoopConnections, "NumberofPlantLoopConnections", "Number of Plant Loop Connections"},
{ PlantComponent_UserDefinedFields::PlantConnection1InletNodeName, "PlantConnection1InletNodeName", "Plant Connection 1 Inlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection1OutletNodeName, "PlantConnection1OutletNodeName", "Plant Connection 1 Outlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection1LoadingMode, "PlantConnection1LoadingMode", "Plant Connection 1 Loading Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection1LoopFlowRequestMode, "PlantConnection1LoopFlowRequestMode", "Plant Connection 1 Loop Flow Request Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection1InitializationProgramCallingManagerName, "PlantConnection1InitializationProgramCallingManagerName", "Plant Connection 1 Initialization Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::PlantConnection1SimulationProgramCallingManagerName, "PlantConnection1SimulationProgramCallingManagerName", "Plant Connection 1 Simulation Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::PlantConnection2InletNodeName, "PlantConnection2InletNodeName", "Plant Connection 2 Inlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection2OutletNodeName, "PlantConnection2OutletNodeName", "Plant Connection 2 Outlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection2LoadingMode, "PlantConnection2LoadingMode", "Plant Connection 2 Loading Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection2LoopFlowRequestMode, "PlantConnection2LoopFlowRequestMode", "Plant Connection 2 Loop Flow Request Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection2InitializationProgramCallingManagerName, "PlantConnection2InitializationProgramCallingManagerName", "Plant Connection 2 Initialization Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::PlantConnection2SimulationProgramCallingManagerName, "PlantConnection2SimulationProgramCallingManagerName", "Plant Connection 2 Simulation Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::PlantConnection3InletNodeName, "PlantConnection3InletNodeName", "Plant Connection 3 Inlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection3OutletNodeName, "PlantConnection3OutletNodeName", "Plant Connection 3 Outlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection3LoadingMode, "PlantConnection3LoadingMode", "Plant Connection 3 Loading Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection3LoopFlowRequestMode, "PlantConnection3LoopFlowRequestMode", "Plant Connection 3 Loop Flow Request Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection3InitializationProgramCallingManagerName, "PlantConnection3InitializationProgramCallingManagerName", "Plant Connection 3 Initialization Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::PlantConnection3SimulationProgramCallingManagerName, "PlantConnection3SimulationProgramCallingManagerName", "Plant Connection 3 Simulation Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::PlantConnection4InletNodeName, "PlantConnection4InletNodeName", "Plant Connection 4 Inlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection4OutletNodeName, "PlantConnection4OutletNodeName", "Plant Connection 4 Outlet Node Name"},
{ PlantComponent_UserDefinedFields::PlantConnection4LoadingMode, "PlantConnection4LoadingMode", "Plant Connection 4 Loading Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection4LoopFlowRequestMode, "PlantConnection4LoopFlowRequestMode", "Plant Connection 4 Loop Flow Request Mode"},
{ PlantComponent_UserDefinedFields::PlantConnection4InitializationProgramCallingManagerName, "PlantConnection4InitializationProgramCallingManagerName", "Plant Connection 4 Initialization Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::PlantConnection4SimulationProgramCallingManagerName, "PlantConnection4SimulationProgramCallingManagerName", "Plant Connection 4 Simulation Program Calling Manager Name"},
{ PlantComponent_UserDefinedFields::AirConnectionInletNodeName, "AirConnectionInletNodeName", "Air Connection Inlet Node Name"},
{ PlantComponent_UserDefinedFields::AirConnectionOutletNodeName, "AirConnectionOutletNodeName", "Air Connection Outlet Node Name"},
{ PlantComponent_UserDefinedFields::SupplyInletWaterStorageTankName, "SupplyInletWaterStorageTankName", "Supply Inlet Water Storage Tank Name"},
{ PlantComponent_UserDefinedFields::CollectionOutletWaterStorageTankName, "CollectionOutletWaterStorageTankName", "Collection Outlet Water Storage Tank Name"},
{ PlantComponent_UserDefinedFields::AmbientZoneName, "AmbientZoneName", "Ambient Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantComponent_UserDefinedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantComponent_UserDefinedFields> OptionalPlantComponent_UserDefinedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTCOMPONENT_USERDEFINED_FIELDENUMS_HXX

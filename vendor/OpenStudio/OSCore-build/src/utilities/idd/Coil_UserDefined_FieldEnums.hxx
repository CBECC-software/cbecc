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

#ifndef UTILITIES_IDD_COIL_USERDEFINED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_USERDEFINED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_UserDefinedFields
 *  \brief Enumeration of Coil:UserDefined's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_UserDefinedFields, )
#else
class Coil_UserDefinedFields: public ::EnumBase<Coil_UserDefinedFields> {
 public: 
  enum domain 
  {
Name, OverallModelSimulationProgramCallingManagerName, ModelSetupandSizingProgramCallingManagerName, NumberofAirConnections, AirConnection1InletNodeName, AirConnection1OutletNodeName, AirConnection2InletNodeName, AirConnection2OutletNodeName, PlantConnectionisUsed, PlantConnectionInletNodeName, PlantConnectionOutletNodeName, SupplyInletWaterStorageTankName, CollectionOutletWaterStorageTankName, AmbientZoneName,   };
  Coil_UserDefinedFields()
   : EnumBase<Coil_UserDefinedFields>(Name) {} 
  Coil_UserDefinedFields(const std::string &t_name) 
   : EnumBase<Coil_UserDefinedFields>(t_name) {} 
  Coil_UserDefinedFields(int t_value) 
   : EnumBase<Coil_UserDefinedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_UserDefinedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_UserDefinedFields>::value()); }
   private:
    friend class EnumBase<Coil_UserDefinedFields>;
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
{ Coil_UserDefinedFields::Name, "Name", "Name"},
{ Coil_UserDefinedFields::OverallModelSimulationProgramCallingManagerName, "OverallModelSimulationProgramCallingManagerName", "Overall Model Simulation Program Calling Manager Name"},
{ Coil_UserDefinedFields::ModelSetupandSizingProgramCallingManagerName, "ModelSetupandSizingProgramCallingManagerName", "Model Setup and Sizing Program Calling Manager Name"},
{ Coil_UserDefinedFields::NumberofAirConnections, "NumberofAirConnections", "Number of Air Connections"},
{ Coil_UserDefinedFields::AirConnection1InletNodeName, "AirConnection1InletNodeName", "Air Connection 1 Inlet Node Name"},
{ Coil_UserDefinedFields::AirConnection1OutletNodeName, "AirConnection1OutletNodeName", "Air Connection 1 Outlet Node Name"},
{ Coil_UserDefinedFields::AirConnection2InletNodeName, "AirConnection2InletNodeName", "Air Connection 2 Inlet Node Name"},
{ Coil_UserDefinedFields::AirConnection2OutletNodeName, "AirConnection2OutletNodeName", "Air Connection 2 Outlet Node Name"},
{ Coil_UserDefinedFields::PlantConnectionisUsed, "PlantConnectionisUsed", "Plant Connection is Used"},
{ Coil_UserDefinedFields::PlantConnectionInletNodeName, "PlantConnectionInletNodeName", "Plant Connection Inlet Node Name"},
{ Coil_UserDefinedFields::PlantConnectionOutletNodeName, "PlantConnectionOutletNodeName", "Plant Connection Outlet Node Name"},
{ Coil_UserDefinedFields::SupplyInletWaterStorageTankName, "SupplyInletWaterStorageTankName", "Supply Inlet Water Storage Tank Name"},
{ Coil_UserDefinedFields::CollectionOutletWaterStorageTankName, "CollectionOutletWaterStorageTankName", "Collection Outlet Water Storage Tank Name"},
{ Coil_UserDefinedFields::AmbientZoneName, "AmbientZoneName", "Ambient Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_UserDefinedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_UserDefinedFields> OptionalCoil_UserDefinedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_USERDEFINED_FIELDENUMS_HXX

/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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

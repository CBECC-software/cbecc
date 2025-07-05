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

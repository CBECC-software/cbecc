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

#ifndef UTILITIES_IDD_OS_PLANTCOMPONENT_USERDEFINED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PLANTCOMPONENT_USERDEFINED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PlantComponent_UserDefinedFields
 *  \brief Enumeration of OS:PlantComponent:UserDefined's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PlantComponent_UserDefinedFields, )
#else
class OS_PlantComponent_UserDefinedFields: public ::EnumBase<OS_PlantComponent_UserDefinedFields> {
 public: 
  enum domain 
  {
Handle, Name, MainModelProgramCallingManagerName, MainModelProgramName, PlantInletNodeName, PlantOutletNodeName, PlantLoadingMode, PlantLoopFlowRequestMode, PlantInitializationProgramCallingManagerName, PlantInitializationProgramName, PlantSimulationProgramCallingManagerName, PlantSimulationProgramName, DesignVolumeFlowRateActuator, MinimumMassFlowRateActuator, MaximumMassFlowRateActuator, MinimumLoadingCapacityActuator, MaximumLoadingCapacityActuator, OptimalLoadingCapacityActuator, OutletTemperatureActuator, MassFlowRateActuator, AmbientZoneName,   };
  OS_PlantComponent_UserDefinedFields()
   : EnumBase<OS_PlantComponent_UserDefinedFields>(Handle) {} 
  OS_PlantComponent_UserDefinedFields(const std::string &t_name) 
   : EnumBase<OS_PlantComponent_UserDefinedFields>(t_name) {} 
  OS_PlantComponent_UserDefinedFields(int t_value) 
   : EnumBase<OS_PlantComponent_UserDefinedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantComponent_UserDefinedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantComponent_UserDefinedFields>::value()); }
   private:
    friend class EnumBase<OS_PlantComponent_UserDefinedFields>;
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
{ OS_PlantComponent_UserDefinedFields::Handle, "Handle", "Handle"},
{ OS_PlantComponent_UserDefinedFields::Name, "Name", "Name"},
{ OS_PlantComponent_UserDefinedFields::MainModelProgramCallingManagerName, "MainModelProgramCallingManagerName", "Main Model Program Calling Manager Name"},
{ OS_PlantComponent_UserDefinedFields::MainModelProgramName, "MainModelProgramName", "Main Model Program Name"},
{ OS_PlantComponent_UserDefinedFields::PlantInletNodeName, "PlantInletNodeName", "Plant Inlet Node Name"},
{ OS_PlantComponent_UserDefinedFields::PlantOutletNodeName, "PlantOutletNodeName", "Plant Outlet Node Name"},
{ OS_PlantComponent_UserDefinedFields::PlantLoadingMode, "PlantLoadingMode", "Plant Loading Mode"},
{ OS_PlantComponent_UserDefinedFields::PlantLoopFlowRequestMode, "PlantLoopFlowRequestMode", "Plant Loop Flow Request Mode"},
{ OS_PlantComponent_UserDefinedFields::PlantInitializationProgramCallingManagerName, "PlantInitializationProgramCallingManagerName", "Plant Initialization Program Calling Manager Name"},
{ OS_PlantComponent_UserDefinedFields::PlantInitializationProgramName, "PlantInitializationProgramName", "Plant Initialization Program Name"},
{ OS_PlantComponent_UserDefinedFields::PlantSimulationProgramCallingManagerName, "PlantSimulationProgramCallingManagerName", "Plant Simulation Program Calling Manager Name"},
{ OS_PlantComponent_UserDefinedFields::PlantSimulationProgramName, "PlantSimulationProgramName", "Plant Simulation Program Name"},
{ OS_PlantComponent_UserDefinedFields::DesignVolumeFlowRateActuator, "DesignVolumeFlowRateActuator", "Design Volume Flow Rate Actuator"},
{ OS_PlantComponent_UserDefinedFields::MinimumMassFlowRateActuator, "MinimumMassFlowRateActuator", "Minimum Mass Flow Rate Actuator"},
{ OS_PlantComponent_UserDefinedFields::MaximumMassFlowRateActuator, "MaximumMassFlowRateActuator", "Maximum Mass Flow Rate Actuator"},
{ OS_PlantComponent_UserDefinedFields::MinimumLoadingCapacityActuator, "MinimumLoadingCapacityActuator", "Minimum Loading Capacity Actuator"},
{ OS_PlantComponent_UserDefinedFields::MaximumLoadingCapacityActuator, "MaximumLoadingCapacityActuator", "Maximum Loading Capacity Actuator"},
{ OS_PlantComponent_UserDefinedFields::OptimalLoadingCapacityActuator, "OptimalLoadingCapacityActuator", "Optimal Loading Capacity Actuator"},
{ OS_PlantComponent_UserDefinedFields::OutletTemperatureActuator, "OutletTemperatureActuator", "Outlet Temperature Actuator"},
{ OS_PlantComponent_UserDefinedFields::MassFlowRateActuator, "MassFlowRateActuator", "Mass Flow Rate Actuator"},
{ OS_PlantComponent_UserDefinedFields::AmbientZoneName, "AmbientZoneName", "Ambient Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantComponent_UserDefinedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantComponent_UserDefinedFields> OptionalOS_PlantComponent_UserDefinedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PLANTCOMPONENT_USERDEFINED_FIELDENUMS_HXX

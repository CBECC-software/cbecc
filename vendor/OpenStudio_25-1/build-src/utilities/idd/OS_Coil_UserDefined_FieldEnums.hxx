/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_USERDEFINED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_USERDEFINED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_UserDefinedFields
 *  \brief Enumeration of OS:Coil:UserDefined's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_UserDefinedFields, )
#else
class OS_Coil_UserDefinedFields: public ::EnumBase<OS_Coil_UserDefinedFields> {
 public: 
  enum domain 
  {
Handle, Name, OverallModelSimulationProgramCallingManagerName, ModelSetupandSizingProgramCallingManagerName, AirConnection1InletNodeName, AirConnection1OutletNodeName, PlantConnectionInletNodeName, PlantConnectionOutletNodeName, AmbientZoneName, OverallSimulationProgramName, InitializationSimulationProgramName, AirOutletTemperatureActuator, AirOutletHumidityRatioActuator, AirMassFlowRateActuator, PlantMinimumMassFlowRateActuator, PlantMaximumMassFlowRateActuator, PlantDesignVolumeFlowRateActuator, PlantOutletTemperatureActuator, PlantMassFlowRateActuator,   };
  OS_Coil_UserDefinedFields()
   : EnumBase<OS_Coil_UserDefinedFields>(Handle) {} 
  OS_Coil_UserDefinedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_UserDefinedFields>(t_name) {} 
  OS_Coil_UserDefinedFields(int t_value) 
   : EnumBase<OS_Coil_UserDefinedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_UserDefinedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_UserDefinedFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_UserDefinedFields>;
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
{ OS_Coil_UserDefinedFields::Handle, "Handle", "Handle"},
{ OS_Coil_UserDefinedFields::Name, "Name", "Name"},
{ OS_Coil_UserDefinedFields::OverallModelSimulationProgramCallingManagerName, "OverallModelSimulationProgramCallingManagerName", "Overall Model Simulation Program Calling Manager Name"},
{ OS_Coil_UserDefinedFields::ModelSetupandSizingProgramCallingManagerName, "ModelSetupandSizingProgramCallingManagerName", "Model Setup and Sizing Program Calling Manager Name"},
{ OS_Coil_UserDefinedFields::AirConnection1InletNodeName, "AirConnection1InletNodeName", "Air Connection 1 Inlet Node Name"},
{ OS_Coil_UserDefinedFields::AirConnection1OutletNodeName, "AirConnection1OutletNodeName", "Air Connection 1 Outlet Node Name"},
{ OS_Coil_UserDefinedFields::PlantConnectionInletNodeName, "PlantConnectionInletNodeName", "Plant Connection Inlet Node Name"},
{ OS_Coil_UserDefinedFields::PlantConnectionOutletNodeName, "PlantConnectionOutletNodeName", "Plant Connection Outlet Node Name"},
{ OS_Coil_UserDefinedFields::AmbientZoneName, "AmbientZoneName", "Ambient Zone Name"},
{ OS_Coil_UserDefinedFields::OverallSimulationProgramName, "OverallSimulationProgramName", "Overall Simulation Program Name"},
{ OS_Coil_UserDefinedFields::InitializationSimulationProgramName, "InitializationSimulationProgramName", "Initialization Simulation Program Name"},
{ OS_Coil_UserDefinedFields::AirOutletTemperatureActuator, "AirOutletTemperatureActuator", "Air Outlet Temperature Actuator"},
{ OS_Coil_UserDefinedFields::AirOutletHumidityRatioActuator, "AirOutletHumidityRatioActuator", "Air Outlet Humidity Ratio Actuator"},
{ OS_Coil_UserDefinedFields::AirMassFlowRateActuator, "AirMassFlowRateActuator", "Air Mass Flow Rate Actuator"},
{ OS_Coil_UserDefinedFields::PlantMinimumMassFlowRateActuator, "PlantMinimumMassFlowRateActuator", "Plant Minimum Mass Flow Rate Actuator"},
{ OS_Coil_UserDefinedFields::PlantMaximumMassFlowRateActuator, "PlantMaximumMassFlowRateActuator", "Plant Maximum Mass Flow Rate Actuator"},
{ OS_Coil_UserDefinedFields::PlantDesignVolumeFlowRateActuator, "PlantDesignVolumeFlowRateActuator", "Plant Design Volume Flow Rate Actuator"},
{ OS_Coil_UserDefinedFields::PlantOutletTemperatureActuator, "PlantOutletTemperatureActuator", "Plant Outlet Temperature Actuator"},
{ OS_Coil_UserDefinedFields::PlantMassFlowRateActuator, "PlantMassFlowRateActuator", "Plant Mass Flow Rate Actuator"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_UserDefinedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_UserDefinedFields> OptionalOS_Coil_UserDefinedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_USERDEFINED_FIELDENUMS_HXX

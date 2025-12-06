/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
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
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantComponent_UserDefinedFields>::integer_value()); }
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

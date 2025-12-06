/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_FAN_COMPONENTMODEL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FAN_COMPONENTMODEL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Fan_ComponentModelFields
 *  \brief Enumeration of OS:Fan:ComponentModel's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Fan_ComponentModelFields, )
#else
class OS_Fan_ComponentModelFields: public ::EnumBase<OS_Fan_ComponentModelFields> {
 public: 
  enum domain 
  {
Handle, Name, AirInletNodeName, AirOutletNodeName, AvailabilityScheduleName, MaximumFlowRate, MinimumFlowRate, FanSizingFactor, FanWheelDiameter, FanOutletArea, MaximumFanStaticEfficiency, EulerNumberatMaximumFanStaticEfficiency, MaximumDimensionlessFanAirflow, MotorFanPulleyRatio, BeltMaximumTorque, BeltSizingFactor, BeltFractionalTorqueTransition, MotorMaximumSpeed, MaximumMotorOutputPower, MotorSizingFactor, MotorInAirstreamFraction, VFDEfficiencyType, MaximumVFDOutputPower, VFDSizingFactor, FanPressureRiseCurveName, DuctStaticPressureResetCurveName, NormalizedFanStaticEfficiencyCurveNameNonStallRegion, NormalizedFanStaticEfficiencyCurveNameStallRegion, NormalizedDimensionlessAirflowCurveNameNonStallRegion, NormalizedDimensionlessAirflowCurveNameStallRegion, MaximumBeltEfficiencyCurveName, NormalizedBeltEfficiencyCurveNameRegion1, NormalizedBeltEfficiencyCurveNameRegion2, NormalizedBeltEfficiencyCurveNameRegion3, MaximumMotorEfficiencyCurveName, NormalizedMotorEfficiencyCurveName, VFDEfficiencyCurveName, EndUseSubcategory,   };
  OS_Fan_ComponentModelFields()
   : EnumBase<OS_Fan_ComponentModelFields>(Handle) {} 
  OS_Fan_ComponentModelFields(const std::string &t_name) 
   : EnumBase<OS_Fan_ComponentModelFields>(t_name) {} 
  OS_Fan_ComponentModelFields(int t_value) 
   : EnumBase<OS_Fan_ComponentModelFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Fan_ComponentModelFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Fan_ComponentModelFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Fan_ComponentModelFields>;
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
{ OS_Fan_ComponentModelFields::Handle, "Handle", "Handle"},
{ OS_Fan_ComponentModelFields::Name, "Name", "Name"},
{ OS_Fan_ComponentModelFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Fan_ComponentModelFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Fan_ComponentModelFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Fan_ComponentModelFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ OS_Fan_ComponentModelFields::MinimumFlowRate, "MinimumFlowRate", "Minimum Flow Rate"},
{ OS_Fan_ComponentModelFields::FanSizingFactor, "FanSizingFactor", "Fan Sizing Factor"},
{ OS_Fan_ComponentModelFields::FanWheelDiameter, "FanWheelDiameter", "Fan Wheel Diameter"},
{ OS_Fan_ComponentModelFields::FanOutletArea, "FanOutletArea", "Fan Outlet Area"},
{ OS_Fan_ComponentModelFields::MaximumFanStaticEfficiency, "MaximumFanStaticEfficiency", "Maximum Fan Static Efficiency"},
{ OS_Fan_ComponentModelFields::EulerNumberatMaximumFanStaticEfficiency, "EulerNumberatMaximumFanStaticEfficiency", "Euler Number at Maximum Fan Static Efficiency"},
{ OS_Fan_ComponentModelFields::MaximumDimensionlessFanAirflow, "MaximumDimensionlessFanAirflow", "Maximum Dimensionless Fan Airflow"},
{ OS_Fan_ComponentModelFields::MotorFanPulleyRatio, "MotorFanPulleyRatio", "Motor Fan Pulley Ratio"},
{ OS_Fan_ComponentModelFields::BeltMaximumTorque, "BeltMaximumTorque", "Belt Maximum Torque"},
{ OS_Fan_ComponentModelFields::BeltSizingFactor, "BeltSizingFactor", "Belt Sizing Factor"},
{ OS_Fan_ComponentModelFields::BeltFractionalTorqueTransition, "BeltFractionalTorqueTransition", "Belt Fractional Torque Transition"},
{ OS_Fan_ComponentModelFields::MotorMaximumSpeed, "MotorMaximumSpeed", "Motor Maximum Speed"},
{ OS_Fan_ComponentModelFields::MaximumMotorOutputPower, "MaximumMotorOutputPower", "Maximum Motor Output Power"},
{ OS_Fan_ComponentModelFields::MotorSizingFactor, "MotorSizingFactor", "Motor Sizing Factor"},
{ OS_Fan_ComponentModelFields::MotorInAirstreamFraction, "MotorInAirstreamFraction", "Motor In Airstream Fraction"},
{ OS_Fan_ComponentModelFields::VFDEfficiencyType, "VFDEfficiencyType", "VFD Efficiency Type"},
{ OS_Fan_ComponentModelFields::MaximumVFDOutputPower, "MaximumVFDOutputPower", "Maximum VFD Output Power"},
{ OS_Fan_ComponentModelFields::VFDSizingFactor, "VFDSizingFactor", "VFD Sizing Factor"},
{ OS_Fan_ComponentModelFields::FanPressureRiseCurveName, "FanPressureRiseCurveName", "Fan Pressure Rise Curve Name"},
{ OS_Fan_ComponentModelFields::DuctStaticPressureResetCurveName, "DuctStaticPressureResetCurveName", "Duct Static Pressure Reset Curve Name"},
{ OS_Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameNonStallRegion, "NormalizedFanStaticEfficiencyCurveNameNonStallRegion", "Normalized Fan Static Efficiency Curve Name-Non-Stall Region"},
{ OS_Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameStallRegion, "NormalizedFanStaticEfficiencyCurveNameStallRegion", "Normalized Fan Static Efficiency Curve Name-Stall Region"},
{ OS_Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameNonStallRegion, "NormalizedDimensionlessAirflowCurveNameNonStallRegion", "Normalized Dimensionless Airflow Curve Name-Non-Stall Region"},
{ OS_Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameStallRegion, "NormalizedDimensionlessAirflowCurveNameStallRegion", "Normalized Dimensionless Airflow Curve Name-Stall Region"},
{ OS_Fan_ComponentModelFields::MaximumBeltEfficiencyCurveName, "MaximumBeltEfficiencyCurveName", "Maximum Belt Efficiency Curve Name"},
{ OS_Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion1, "NormalizedBeltEfficiencyCurveNameRegion1", "Normalized Belt Efficiency Curve Name - Region 1"},
{ OS_Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion2, "NormalizedBeltEfficiencyCurveNameRegion2", "Normalized Belt Efficiency Curve Name - Region 2"},
{ OS_Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion3, "NormalizedBeltEfficiencyCurveNameRegion3", "Normalized Belt Efficiency Curve Name - Region 3"},
{ OS_Fan_ComponentModelFields::MaximumMotorEfficiencyCurveName, "MaximumMotorEfficiencyCurveName", "Maximum Motor Efficiency Curve Name"},
{ OS_Fan_ComponentModelFields::NormalizedMotorEfficiencyCurveName, "NormalizedMotorEfficiencyCurveName", "Normalized Motor Efficiency Curve Name"},
{ OS_Fan_ComponentModelFields::VFDEfficiencyCurveName, "VFDEfficiencyCurveName", "VFD Efficiency Curve Name"},
{ OS_Fan_ComponentModelFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Fan_ComponentModelFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Fan_ComponentModelFields> OptionalOS_Fan_ComponentModelFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FAN_COMPONENTMODEL_FIELDENUMS_HXX

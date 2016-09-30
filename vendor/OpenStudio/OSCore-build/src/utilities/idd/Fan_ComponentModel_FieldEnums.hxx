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

#ifndef UTILITIES_IDD_FAN_COMPONENTMODEL_FIELDENUMS_HXX
#define UTILITIES_IDD_FAN_COMPONENTMODEL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Fan_ComponentModelFields
 *  \brief Enumeration of Fan:ComponentModel's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Fan_ComponentModelFields, )
#else
class Fan_ComponentModelFields: public ::EnumBase<Fan_ComponentModelFields> {
 public: 
  enum domain 
  {
Name, AirInletNodeName, AirOutletNodeName, AvailabilityScheduleName, MaximumFlowRate, MinimumFlowRate, FanSizingFactor, FanWheelDiameter, FanOutletArea, MaximumFanStaticEfficiency, EulerNumberatMaximumFanStaticEfficiency, MaximumDimensionlessFanAirflow, MotorFanPulleyRatio, BeltMaximumTorque, BeltSizingFactor, BeltFractionalTorqueTransition, MotorMaximumSpeed, MaximumMotorOutputPower, MotorSizingFactor, MotorInAirstreamFraction, VFDEfficiencyType, MaximumVFDOutputPower, VFDSizingFactor, FanPressureRiseCurveName, DuctStaticPressureResetCurveName, NormalizedFanStaticEfficiencyCurveNameNonStallRegion, NormalizedFanStaticEfficiencyCurveNameStallRegion, NormalizedDimensionlessAirflowCurveNameNonStallRegion, NormalizedDimensionlessAirflowCurveNameStallRegion, MaximumBeltEfficiencyCurveName, NormalizedBeltEfficiencyCurveNameRegion1, NormalizedBeltEfficiencyCurveNameRegion2, NormalizedBeltEfficiencyCurveNameRegion3, MaximumMotorEfficiencyCurveName, NormalizedMotorEfficiencyCurveName, VFDEfficiencyCurveName, EndUseSubcategory,   };
  Fan_ComponentModelFields()
   : EnumBase<Fan_ComponentModelFields>(Name) {} 
  Fan_ComponentModelFields(const std::string &t_name) 
   : EnumBase<Fan_ComponentModelFields>(t_name) {} 
  Fan_ComponentModelFields(int t_value) 
   : EnumBase<Fan_ComponentModelFields>(t_value) {} 
  static std::string enumName() 
  { return "Fan_ComponentModelFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Fan_ComponentModelFields>::value()); }
   private:
    friend class EnumBase<Fan_ComponentModelFields>;
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
{ Fan_ComponentModelFields::Name, "Name", "Name"},
{ Fan_ComponentModelFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Fan_ComponentModelFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Fan_ComponentModelFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Fan_ComponentModelFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ Fan_ComponentModelFields::MinimumFlowRate, "MinimumFlowRate", "Minimum Flow Rate"},
{ Fan_ComponentModelFields::FanSizingFactor, "FanSizingFactor", "Fan Sizing Factor"},
{ Fan_ComponentModelFields::FanWheelDiameter, "FanWheelDiameter", "Fan Wheel Diameter"},
{ Fan_ComponentModelFields::FanOutletArea, "FanOutletArea", "Fan Outlet Area"},
{ Fan_ComponentModelFields::MaximumFanStaticEfficiency, "MaximumFanStaticEfficiency", "Maximum Fan Static Efficiency"},
{ Fan_ComponentModelFields::EulerNumberatMaximumFanStaticEfficiency, "EulerNumberatMaximumFanStaticEfficiency", "Euler Number at Maximum Fan Static Efficiency"},
{ Fan_ComponentModelFields::MaximumDimensionlessFanAirflow, "MaximumDimensionlessFanAirflow", "Maximum Dimensionless Fan Airflow"},
{ Fan_ComponentModelFields::MotorFanPulleyRatio, "MotorFanPulleyRatio", "Motor Fan Pulley Ratio"},
{ Fan_ComponentModelFields::BeltMaximumTorque, "BeltMaximumTorque", "Belt Maximum Torque"},
{ Fan_ComponentModelFields::BeltSizingFactor, "BeltSizingFactor", "Belt Sizing Factor"},
{ Fan_ComponentModelFields::BeltFractionalTorqueTransition, "BeltFractionalTorqueTransition", "Belt Fractional Torque Transition"},
{ Fan_ComponentModelFields::MotorMaximumSpeed, "MotorMaximumSpeed", "Motor Maximum Speed"},
{ Fan_ComponentModelFields::MaximumMotorOutputPower, "MaximumMotorOutputPower", "Maximum Motor Output Power"},
{ Fan_ComponentModelFields::MotorSizingFactor, "MotorSizingFactor", "Motor Sizing Factor"},
{ Fan_ComponentModelFields::MotorInAirstreamFraction, "MotorInAirstreamFraction", "Motor In Airstream Fraction"},
{ Fan_ComponentModelFields::VFDEfficiencyType, "VFDEfficiencyType", "VFD Efficiency Type"},
{ Fan_ComponentModelFields::MaximumVFDOutputPower, "MaximumVFDOutputPower", "Maximum VFD Output Power"},
{ Fan_ComponentModelFields::VFDSizingFactor, "VFDSizingFactor", "VFD Sizing Factor"},
{ Fan_ComponentModelFields::FanPressureRiseCurveName, "FanPressureRiseCurveName", "Fan Pressure Rise Curve Name"},
{ Fan_ComponentModelFields::DuctStaticPressureResetCurveName, "DuctStaticPressureResetCurveName", "Duct Static Pressure Reset Curve Name"},
{ Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameNonStallRegion, "NormalizedFanStaticEfficiencyCurveNameNonStallRegion", "Normalized Fan Static Efficiency Curve Name-Non-Stall Region"},
{ Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameStallRegion, "NormalizedFanStaticEfficiencyCurveNameStallRegion", "Normalized Fan Static Efficiency Curve Name-Stall Region"},
{ Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameNonStallRegion, "NormalizedDimensionlessAirflowCurveNameNonStallRegion", "Normalized Dimensionless Airflow Curve Name-Non-Stall Region"},
{ Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameStallRegion, "NormalizedDimensionlessAirflowCurveNameStallRegion", "Normalized Dimensionless Airflow Curve Name-Stall Region"},
{ Fan_ComponentModelFields::MaximumBeltEfficiencyCurveName, "MaximumBeltEfficiencyCurveName", "Maximum Belt Efficiency Curve Name"},
{ Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion1, "NormalizedBeltEfficiencyCurveNameRegion1", "Normalized Belt Efficiency Curve Name - Region 1"},
{ Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion2, "NormalizedBeltEfficiencyCurveNameRegion2", "Normalized Belt Efficiency Curve Name - Region 2"},
{ Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion3, "NormalizedBeltEfficiencyCurveNameRegion3", "Normalized Belt Efficiency Curve Name - Region 3"},
{ Fan_ComponentModelFields::MaximumMotorEfficiencyCurveName, "MaximumMotorEfficiencyCurveName", "Maximum Motor Efficiency Curve Name"},
{ Fan_ComponentModelFields::NormalizedMotorEfficiencyCurveName, "NormalizedMotorEfficiencyCurveName", "Normalized Motor Efficiency Curve Name"},
{ Fan_ComponentModelFields::VFDEfficiencyCurveName, "VFDEfficiencyCurveName", "VFD Efficiency Curve Name"},
{ Fan_ComponentModelFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Fan_ComponentModelFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Fan_ComponentModelFields> OptionalFan_ComponentModelFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAN_COMPONENTMODEL_FIELDENUMS_HXX

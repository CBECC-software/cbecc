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

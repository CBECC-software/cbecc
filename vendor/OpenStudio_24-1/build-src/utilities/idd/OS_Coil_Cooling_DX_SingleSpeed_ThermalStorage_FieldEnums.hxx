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

#ifndef UTILITIES_IDD_OS_COIL_COOLING_DX_SINGLESPEED_THERMALSTORAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_DX_SINGLESPEED_THERMALSTORAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:SingleSpeed:ThermalStorage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields, )
#else
class OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields: public ::EnumBase<OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, OperatingModeControlMethod, OperationModeControlSchedule, StorageType, GlycolConcentration, FluidStorageVolume, IceStorageCapacity, StorageCapacitySizingFactor, StorageTankAmbientTemperatureNode, StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient, FluidStorageTankRatingTemperature, RatedEvaporatorAirFlowRate, EvaporatorAirInletNode, EvaporatorAirOutletNode, CoolingOnlyModeAvailable, CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity, CoolingOnlyModeRatedSensibleHeatRatio, CoolingOnlyModeRatedCOP, CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve, CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve, CoolingOnlyModeEnergyInputRatioFunctionofTemperatureCurve, CoolingOnlyModeEnergyInputRatioFunctionofFlowFractionCurve, CoolingOnlyModePartLoadFractionCorrelationCurve, CoolingOnlyModeSensibleHeatRatioFunctionofTemperatureCurve, CoolingOnlyModeSensibleHeatRatioFunctionofFlowFractionCurve, CoolingAndChargeModeAvailable, CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity, CoolingAndChargeModeCapacitySizingFactor, CoolingAndChargeModeRatedStorageChargingCapacity, CoolingAndChargeModeStorageCapacitySizingFactor, CoolingAndChargeModeRatedSensibleHeatRatio, CoolingAndChargeModeCoolingRatedCOP, CoolingAndChargeModeChargingRatedCOP, CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve, CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve, CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurve, CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurve, CoolingAndChargeModeEvaporatorPartLoadFractionCorrelationCurve, CoolingAndChargeModeStorageChargeCapacityFunctionofTemperatureCurve, CoolingAndChargeModeStorageChargeCapacityFunctionofTotalEvaporatorPLRCurve, CoolingAndChargeModeStorageEnergyInputRatioFunctionofTemperatureCurve, CoolingAndChargeModeStorageEnergyInputRatioFunctionofFlowFractionCurve, CoolingAndChargeModeStorageEnergyPartLoadFractionCorrelationCurve, CoolingAndChargeModeSensibleHeatRatioFunctionofTemperatureCurve, CoolingAndChargeModeSensibleHeatRatioFunctionofFlowFractionCurve, CoolingAndDischargeModeAvailable, CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity, CoolingAndDischargeModeEvaporatorCapacitySizingFactor, CoolingAndDischargeModeRatedStorageDischargingCapacity, CoolingAndDischargeModeStorageDischargeCapacitySizingFactor, CoolingAndDischargeModeRatedSensibleHeatRatio, CoolingAndDischargeModeCoolingRatedCOP, CoolingAndDischargeModeDischargingRatedCOP, CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve, CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve, CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurve, CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurve, CoolingAndDischargeModeEvaporatorPartLoadFractionCorrelationCurve, CoolingAndDischargeModeStorageDischargeCapacityFunctionofTemperatureCurve, CoolingAndDischargeModeStorageDischargeCapacityFunctionofFlowFractionCurve, CoolingAndDischargeModeStorageDischargeCapacityFunctionofTotalEvaporatorPLRCurve, CoolingAndDischargeModeStorageEnergyInputRatioFunctionofTemperatureCurve, CoolingAndDischargeModeStorageEnergyInputRatioFunctionofFlowFractionCurve, CoolingAndDischargeModeStorageEnergyPartLoadFractionCorrelationCurve, CoolingAndDischargeModeSensibleHeatRatioFunctionofTemperatureCurve, CoolingAndDischargeModeSensibleHeatRatioFunctionofFlowFractionCurve, ChargeOnlyModeAvailable, ChargeOnlyModeRatedStorageChargingCapacity, ChargeOnlyModeCapacitySizingFactor, ChargeOnlyModeChargingRatedCOP, ChargeOnlyModeStorageChargeCapacityFunctionofTemperatureCurve, ChargeOnlyModeStorageEnergyInputRatioFunctionofTemperatureCurve, DischargeOnlyModeAvailable, DischargeOnlyModeRatedStorageDischargingCapacity, DischargeOnlyModeCapacitySizingFactor, DischargeOnlyModeRatedSensibleHeatRatio, DischargeOnlyModeRatedCOP, DischargeOnlyModeStorageDischargeCapacityFunctionofTemperatureCurve, DischargeOnlyModeStorageDischargeCapacityFunctionofFlowFractionCurve, DischargeOnlyModeEnergyInputRatioFunctionofTemperatureCurve, DischargeOnlyModeEnergyInputRatioFunctionofFlowFractionCurve, DischargeOnlyModePartLoadFractionCorrelationCurve, DischargeOnlyModeSensibleHeatRatioFunctionofTemperatureCurve, DischargeOnlyModeSensibleHeatRatioFunctionofFlowFractionCurve, AncillaryElectricPower, ColdWeatherOperationMinimumOutdoorAirTemperature, ColdWeatherOperationAncillaryPower, CondenserAirInletNode, CondenserAirOutletNode, CondenserDesignAirFlowRate, CondenserAirFlowSizingFactor, CondenserType, EvaporativeCondenserEffectiveness, EvaporativeCondenserPumpRatedPowerConsumption, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterAvailabilitySchedule, SupplyWaterStorageTank, CondensateCollectionWaterStorageTank, StorageTankPlantConnectionInletNode, StorageTankPlantConnectionOutletNode, StorageTankPlantConnectionDesignFlowRate, StorageTankPlantConnectionHeatTransferEffectiveness, StorageTankMinimumOperatingLimitFluidTemperature, StorageTankMaximumOperatingLimitFluidTemperature,   };
  OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields()
   : EnumBase<OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>(Handle) {} 
  OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>(t_name) {} 
  OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>;
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
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperatingModeControlMethod, "OperatingModeControlMethod", "Operating Mode Control Method"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperationModeControlSchedule, "OperationModeControlSchedule", "Operation Mode Control Schedule"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageType, "StorageType", "Storage Type"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::GlycolConcentration, "GlycolConcentration", "Glycol Concentration"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageVolume, "FluidStorageVolume", "Fluid Storage Volume"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::IceStorageCapacity, "IceStorageCapacity", "Ice Storage Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageCapacitySizingFactor, "StorageCapacitySizingFactor", "Storage Capacity Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankAmbientTemperatureNode, "StorageTankAmbientTemperatureNode", "Storage Tank Ambient Temperature Node"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient, "StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient", "Storage Tank to Ambient U-value Times Area Heat Transfer Coefficient"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageTankRatingTemperature, "FluidStorageTankRatingTemperature", "Fluid Storage Tank Rating Temperature"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::RatedEvaporatorAirFlowRate, "RatedEvaporatorAirFlowRate", "Rated Evaporator Air Flow Rate"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporatorAirInletNode, "EvaporatorAirInletNode", "Evaporator Air Inlet Node"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporatorAirOutletNode, "EvaporatorAirOutletNode", "Evaporator Air Outlet Node"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeAvailable, "CoolingOnlyModeAvailable", "Cooling Only Mode Available"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity, "CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity", "Cooling Only Mode Rated Total Evaporator Cooling Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedSensibleHeatRatio, "CoolingOnlyModeRatedSensibleHeatRatio", "Cooling Only Mode Rated Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedCOP, "CoolingOnlyModeRatedCOP", "Cooling Only Mode Rated COP"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve, "CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve", "Cooling Only Mode Total Evaporator Cooling Capacity Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve, "CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve", "Cooling Only Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeEnergyInputRatioFunctionofTemperatureCurve, "CoolingOnlyModeEnergyInputRatioFunctionofTemperatureCurve", "Cooling Only Mode Energy Input Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeEnergyInputRatioFunctionofFlowFractionCurve, "CoolingOnlyModeEnergyInputRatioFunctionofFlowFractionCurve", "Cooling Only Mode Energy Input Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModePartLoadFractionCorrelationCurve, "CoolingOnlyModePartLoadFractionCorrelationCurve", "Cooling Only Mode Part Load Fraction Correlation Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeSensibleHeatRatioFunctionofTemperatureCurve, "CoolingOnlyModeSensibleHeatRatioFunctionofTemperatureCurve", "Cooling Only Mode Sensible Heat Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeSensibleHeatRatioFunctionofFlowFractionCurve, "CoolingOnlyModeSensibleHeatRatioFunctionofFlowFractionCurve", "Cooling Only Mode Sensible Heat Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeAvailable, "CoolingAndChargeModeAvailable", "Cooling And Charge Mode Available"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity, "CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity", "Cooling And Charge Mode Rated Total Evaporator Cooling Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCapacitySizingFactor, "CoolingAndChargeModeCapacitySizingFactor", "Cooling And Charge Mode Capacity Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedStorageChargingCapacity, "CoolingAndChargeModeRatedStorageChargingCapacity", "Cooling And Charge Mode Rated Storage Charging Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageCapacitySizingFactor, "CoolingAndChargeModeStorageCapacitySizingFactor", "Cooling And Charge Mode Storage Capacity Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedSensibleHeatRatio, "CoolingAndChargeModeRatedSensibleHeatRatio", "Cooling And Charge Mode Rated Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCoolingRatedCOP, "CoolingAndChargeModeCoolingRatedCOP", "Cooling And Charge Mode Cooling Rated COP"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeChargingRatedCOP, "CoolingAndChargeModeChargingRatedCOP", "Cooling And Charge Mode Charging Rated COP"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve, "CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve", "Cooling And Charge Mode Total Evaporator Cooling Capacity Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve, "CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve", "Cooling And Charge Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurve, "CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurve", "Cooling And Charge Mode Evaporator Energy Input Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurve, "CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurve", "Cooling And Charge Mode Evaporator Energy Input Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeEvaporatorPartLoadFractionCorrelationCurve, "CoolingAndChargeModeEvaporatorPartLoadFractionCorrelationCurve", "Cooling And Charge Mode Evaporator Part Load Fraction Correlation Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageChargeCapacityFunctionofTemperatureCurve, "CoolingAndChargeModeStorageChargeCapacityFunctionofTemperatureCurve", "Cooling And Charge Mode Storage Charge Capacity Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageChargeCapacityFunctionofTotalEvaporatorPLRCurve, "CoolingAndChargeModeStorageChargeCapacityFunctionofTotalEvaporatorPLRCurve", "Cooling And Charge Mode Storage Charge Capacity Function of Total Evaporator PLR Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageEnergyInputRatioFunctionofTemperatureCurve, "CoolingAndChargeModeStorageEnergyInputRatioFunctionofTemperatureCurve", "Cooling And Charge Mode Storage Energy Input Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageEnergyInputRatioFunctionofFlowFractionCurve, "CoolingAndChargeModeStorageEnergyInputRatioFunctionofFlowFractionCurve", "Cooling And Charge Mode Storage Energy Input Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageEnergyPartLoadFractionCorrelationCurve, "CoolingAndChargeModeStorageEnergyPartLoadFractionCorrelationCurve", "Cooling And Charge Mode Storage Energy Part Load Fraction Correlation Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeSensibleHeatRatioFunctionofTemperatureCurve, "CoolingAndChargeModeSensibleHeatRatioFunctionofTemperatureCurve", "Cooling And Charge Mode Sensible Heat Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeSensibleHeatRatioFunctionofFlowFractionCurve, "CoolingAndChargeModeSensibleHeatRatioFunctionofFlowFractionCurve", "Cooling And Charge Mode Sensible Heat Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeAvailable, "CoolingAndDischargeModeAvailable", "Cooling And Discharge Mode Available"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity, "CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity", "Cooling And Discharge Mode Rated Total Evaporator Cooling Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorCapacitySizingFactor, "CoolingAndDischargeModeEvaporatorCapacitySizingFactor", "Cooling And Discharge Mode Evaporator Capacity Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity, "CoolingAndDischargeModeRatedStorageDischargingCapacity", "Cooling And Discharge Mode Rated Storage Discharging Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacitySizingFactor, "CoolingAndDischargeModeStorageDischargeCapacitySizingFactor", "Cooling And Discharge Mode Storage Discharge Capacity Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedSensibleHeatRatio, "CoolingAndDischargeModeRatedSensibleHeatRatio", "Cooling And Discharge Mode Rated Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeCoolingRatedCOP, "CoolingAndDischargeModeCoolingRatedCOP", "Cooling And Discharge Mode Cooling Rated COP"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeDischargingRatedCOP, "CoolingAndDischargeModeDischargingRatedCOP", "Cooling And Discharge Mode Discharging Rated COP"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve, "CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurve", "Cooling And Discharge Mode Total Evaporator Cooling Capacity Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve, "CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurve", "Cooling And Discharge Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurve, "CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurve", "Cooling And Discharge Mode Evaporator Energy Input Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurve, "CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurve", "Cooling And Discharge Mode Evaporator Energy Input Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorPartLoadFractionCorrelationCurve, "CoolingAndDischargeModeEvaporatorPartLoadFractionCorrelationCurve", "Cooling And Discharge Mode Evaporator Part Load Fraction Correlation Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacityFunctionofTemperatureCurve, "CoolingAndDischargeModeStorageDischargeCapacityFunctionofTemperatureCurve", "Cooling And Discharge Mode Storage Discharge Capacity Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacityFunctionofFlowFractionCurve, "CoolingAndDischargeModeStorageDischargeCapacityFunctionofFlowFractionCurve", "Cooling And Discharge Mode Storage Discharge Capacity Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacityFunctionofTotalEvaporatorPLRCurve, "CoolingAndDischargeModeStorageDischargeCapacityFunctionofTotalEvaporatorPLRCurve", "Cooling And Discharge Mode Storage Discharge Capacity Function of Total Evaporator PLR Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageEnergyInputRatioFunctionofTemperatureCurve, "CoolingAndDischargeModeStorageEnergyInputRatioFunctionofTemperatureCurve", "Cooling And Discharge Mode Storage Energy Input Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageEnergyInputRatioFunctionofFlowFractionCurve, "CoolingAndDischargeModeStorageEnergyInputRatioFunctionofFlowFractionCurve", "Cooling And Discharge Mode Storage Energy Input Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageEnergyPartLoadFractionCorrelationCurve, "CoolingAndDischargeModeStorageEnergyPartLoadFractionCorrelationCurve", "Cooling And Discharge Mode Storage Energy Part Load Fraction Correlation Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeSensibleHeatRatioFunctionofTemperatureCurve, "CoolingAndDischargeModeSensibleHeatRatioFunctionofTemperatureCurve", "Cooling And Discharge Mode Sensible Heat Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeSensibleHeatRatioFunctionofFlowFractionCurve, "CoolingAndDischargeModeSensibleHeatRatioFunctionofFlowFractionCurve", "Cooling And Discharge Mode Sensible Heat Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeAvailable, "ChargeOnlyModeAvailable", "Charge Only Mode Available"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity, "ChargeOnlyModeRatedStorageChargingCapacity", "Charge Only Mode Rated Storage Charging Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeCapacitySizingFactor, "ChargeOnlyModeCapacitySizingFactor", "Charge Only Mode Capacity Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeChargingRatedCOP, "ChargeOnlyModeChargingRatedCOP", "Charge Only Mode Charging Rated COP"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeStorageChargeCapacityFunctionofTemperatureCurve, "ChargeOnlyModeStorageChargeCapacityFunctionofTemperatureCurve", "Charge Only Mode Storage Charge Capacity Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeStorageEnergyInputRatioFunctionofTemperatureCurve, "ChargeOnlyModeStorageEnergyInputRatioFunctionofTemperatureCurve", "Charge Only Mode Storage Energy Input Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeAvailable, "DischargeOnlyModeAvailable", "Discharge Only Mode Available"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedStorageDischargingCapacity, "DischargeOnlyModeRatedStorageDischargingCapacity", "Discharge Only Mode Rated Storage Discharging Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeCapacitySizingFactor, "DischargeOnlyModeCapacitySizingFactor", "Discharge Only Mode Capacity Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedSensibleHeatRatio, "DischargeOnlyModeRatedSensibleHeatRatio", "Discharge Only Mode Rated Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedCOP, "DischargeOnlyModeRatedCOP", "Discharge Only Mode Rated COP"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeStorageDischargeCapacityFunctionofTemperatureCurve, "DischargeOnlyModeStorageDischargeCapacityFunctionofTemperatureCurve", "Discharge Only Mode Storage Discharge Capacity Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeStorageDischargeCapacityFunctionofFlowFractionCurve, "DischargeOnlyModeStorageDischargeCapacityFunctionofFlowFractionCurve", "Discharge Only Mode Storage Discharge Capacity Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeEnergyInputRatioFunctionofTemperatureCurve, "DischargeOnlyModeEnergyInputRatioFunctionofTemperatureCurve", "Discharge Only Mode Energy Input Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeEnergyInputRatioFunctionofFlowFractionCurve, "DischargeOnlyModeEnergyInputRatioFunctionofFlowFractionCurve", "Discharge Only Mode Energy Input Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModePartLoadFractionCorrelationCurve, "DischargeOnlyModePartLoadFractionCorrelationCurve", "Discharge Only Mode Part Load Fraction Correlation Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeSensibleHeatRatioFunctionofTemperatureCurve, "DischargeOnlyModeSensibleHeatRatioFunctionofTemperatureCurve", "Discharge Only Mode Sensible Heat Ratio Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeSensibleHeatRatioFunctionofFlowFractionCurve, "DischargeOnlyModeSensibleHeatRatioFunctionofFlowFractionCurve", "Discharge Only Mode Sensible Heat Ratio Function of Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AncillaryElectricPower, "AncillaryElectricPower", "Ancillary Electric Power"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationMinimumOutdoorAirTemperature, "ColdWeatherOperationMinimumOutdoorAirTemperature", "Cold Weather Operation Minimum Outdoor Air Temperature"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationAncillaryPower, "ColdWeatherOperationAncillaryPower", "Cold Weather Operation Ancillary Power"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirInletNode, "CondenserAirInletNode", "Condenser Air Inlet Node"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirOutletNode, "CondenserAirOutletNode", "Condenser Air Outlet Node"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserDesignAirFlowRate, "CondenserDesignAirFlowRate", "Condenser Design Air Flow Rate"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirFlowSizingFactor, "CondenserAirFlowSizingFactor", "Condenser Air Flow Sizing Factor"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterAvailabilitySchedule, "BasinHeaterAvailabilitySchedule", "Basin Heater Availability Schedule"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::SupplyWaterStorageTank, "SupplyWaterStorageTank", "Supply Water Storage Tank"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondensateCollectionWaterStorageTank, "CondensateCollectionWaterStorageTank", "Condensate Collection Water Storage Tank"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionInletNode, "StorageTankPlantConnectionInletNode", "Storage Tank Plant Connection Inlet Node"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionOutletNode, "StorageTankPlantConnectionOutletNode", "Storage Tank Plant Connection Outlet Node"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionDesignFlowRate, "StorageTankPlantConnectionDesignFlowRate", "Storage Tank Plant Connection Design Flow Rate"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionHeatTransferEffectiveness, "StorageTankPlantConnectionHeatTransferEffectiveness", "Storage Tank Plant Connection Heat Transfer Effectiveness"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankMinimumOperatingLimitFluidTemperature, "StorageTankMinimumOperatingLimitFluidTemperature", "Storage Tank Minimum Operating Limit Fluid Temperature"},
{ OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankMaximumOperatingLimitFluidTemperature, "StorageTankMaximumOperatingLimitFluidTemperature", "Storage Tank Maximum Operating Limit Fluid Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields> OptionalOS_Coil_Cooling_DX_SingleSpeed_ThermalStorageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_DX_SINGLESPEED_THERMALSTORAGE_FIELDENUMS_HXX

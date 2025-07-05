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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_SINGLESPEED_THERMALSTORAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_SINGLESPEED_THERMALSTORAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_SingleSpeed_ThermalStorageFields
 *  \brief Enumeration of Coil:Cooling:DX:SingleSpeed:ThermalStorage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_SingleSpeed_ThermalStorageFields, )
#else
class Coil_Cooling_DX_SingleSpeed_ThermalStorageFields: public ::EnumBase<Coil_Cooling_DX_SingleSpeed_ThermalStorageFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, OperatingModeControlMethod, OperationModeControlScheduleName, StorageType, UserDefinedFluidType, FluidStorageVolume, IceStorageCapacity, StorageCapacitySizingFactor, StorageTankAmbientTemperatureNodeName, StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient, FluidStorageTankRatingTemperature, RatedEvaporatorAirFlowRate, EvaporatorAirInletNodeName, EvaporatorAirOutletNodeName, CoolingOnlyModeAvailable, CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity, CoolingOnlyModeRatedSensibleHeatRatio, CoolingOnlyModeRatedCOP, CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName, CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName, CoolingOnlyModeEnergyInputRatioFunctionofTemperatureCurveName, CoolingOnlyModeEnergyInputRatioFunctionofFlowFractionCurveName, CoolingOnlyModePartLoadFractionCorrelationCurveName, CoolingOnlyModeSensibleHeatRatioFunctionofTemperatureCurveName, CoolingOnlyModeSensibleHeatRatioFunctionofFlowFractionCurveName, CoolingAndChargeModeAvailable, CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity, CoolingAndChargeModeCapacitySizingFactor, CoolingAndChargeModeRatedStorageChargingCapacity, CoolingAndChargeModeStorageCapacitySizingFactor, CoolingAndChargeModeRatedSensibleHeatRatio, CoolingAndChargeModeCoolingRatedCOP, CoolingAndChargeModeChargingRatedCOP, CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName, CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName, CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurveName, CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurveName, CoolingAndChargeModeEvaporatorPartLoadFractionCorrelationCurveName, CoolingAndChargeModeStorageChargeCapacityFunctionofTemperatureCurveName, CoolingAndChargeModeStorageChargeCapacityFunctionofTotalEvaporatorPLRCurveName, CoolingAndChargeModeStorageEnergyInputRatioFunctionofTemperatureCurveName, CoolingAndChargeModeStorageEnergyInputRatioFunctionofFlowFractionCurveName, CoolingAndChargeModeStorageEnergyPartLoadFractionCorrelationCurveName, CoolingAndChargeModeSensibleHeatRatioFunctionofTemperatureCurveName, CoolingAndChargeModeSensibleHeatRatioFunctionofFlowFractionCurveName, CoolingAndDischargeModeAvailable, CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity, CoolingAndDischargeModeEvaporatorCapacitySizingFactor, CoolingAndDischargeModeRatedStorageDischargingCapacity, CoolingAndDischargeModeStorageDischargeCapacitySizingFactor, CoolingAndDischargeModeRatedSensibleHeatRatio, CoolingAndDischargeModeCoolingRatedCOP, CoolingAndDischargeModeDischargingRatedCOP, CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName, CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName, CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurveName, CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurveName, CoolingAndDischargeModeEvaporatorPartLoadFractionCorrelationCurveName, CoolingAndDischargeModeStorageDischargeCapacityFunctionofTemperatureCurveName, CoolingAndDischargeModeStorageDischargeCapacityFunctionofFlowFractionCurveName, CoolingAndDischargeModeStorageDischargeCapacityFunctionofTotalEvaporatorPLRCurveName, CoolingAndDischargeModeStorageEnergyInputRatioFunctionofTemperatureCurveName, CoolingAndDischargeModeStorageEnergyInputRatioFunctionofFlowFractionCurveName, CoolingAndDischargeModeStorageEnergyPartLoadFractionCorrelationCurveName, CoolingAndDischargeModeSensibleHeatRatioFunctionofTemperatureCurveName, CoolingAndDischargeModeSensibleHeatRatioFunctionofFlowFractionCurveName, ChargeOnlyModeAvailable, ChargeOnlyModeRatedStorageChargingCapacity, ChargeOnlyModeCapacitySizingFactor, ChargeOnlyModeChargingRatedCOP, ChargeOnlyModeStorageChargeCapacityFunctionofTemperatureCurveName, ChargeOnlyModeStorageEnergyInputRatioFunctionofTemperatureCurveName, DischargeOnlyModeAvailable, DischargeOnlyModeRatedStorageDischargingCapacity, DischargeOnlyModeCapacitySizingFactor, DischargeOnlyModeRatedSensibleHeatRatio, DischargeOnlyModeRatedCOP, DischargeOnlyModeStorageDischargeCapacityFunctionofTemperatureCurveName, DischargeOnlyModeStorageDischargeCapacityFunctionofFlowFractionCurveName, DischargeOnlyModeEnergyInputRatioFunctionofTemperatureCurveName, DischargeOnlyModeEnergyInputRatioFunctionofFlowFractionCurveName, DischargeOnlyModePartLoadFractionCorrelationCurveName, DischargeOnlyModeSensibleHeatRatioFunctionofTemperatureCurveName, DischargeOnlyModeSensibleHeatRatioFunctionofFlowFractionCurveName, AncillaryElectricPower, ColdWeatherOperationMinimumOutdoorAirTemperature, ColdWeatherOperationAncillaryPower, CondenserAirInletNodeName, CondenserAirOutletNodeName, CondenserDesignAirFlowRate, CondenserAirFlowSizingFactor, CondenserType, EvaporativeCondenserEffectiveness, EvaporativeCondenserPumpRatedPowerConsumption, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterAvailabilityScheduleName, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, StorageTankPlantConnectionInletNodeName, StorageTankPlantConnectionOutletNodeName, StorageTankPlantConnectionDesignFlowRate, StorageTankPlantConnectionHeatTransferEffectiveness, StorageTankMinimumOperatingLimitFluidTemperature, StorageTankMaximumOperatingLimitFluidTemperature,   };
  Coil_Cooling_DX_SingleSpeed_ThermalStorageFields()
   : EnumBase<Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>(Name) {} 
  Coil_Cooling_DX_SingleSpeed_ThermalStorageFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>(t_name) {} 
  Coil_Cooling_DX_SingleSpeed_ThermalStorageFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_SingleSpeed_ThermalStorageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_SingleSpeed_ThermalStorageFields>;
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
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperatingModeControlMethod, "OperatingModeControlMethod", "Operating Mode Control Method"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperationModeControlScheduleName, "OperationModeControlScheduleName", "Operation Mode Control Schedule Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageType, "StorageType", "Storage Type"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::UserDefinedFluidType, "UserDefinedFluidType", "User Defined Fluid Type"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageVolume, "FluidStorageVolume", "Fluid Storage Volume"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::IceStorageCapacity, "IceStorageCapacity", "Ice Storage Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageCapacitySizingFactor, "StorageCapacitySizingFactor", "Storage Capacity Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankAmbientTemperatureNodeName, "StorageTankAmbientTemperatureNodeName", "Storage Tank Ambient Temperature Node Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient, "StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient", "Storage Tank to Ambient U-value Times Area Heat Transfer Coefficient"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageTankRatingTemperature, "FluidStorageTankRatingTemperature", "Fluid Storage Tank Rating Temperature"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::RatedEvaporatorAirFlowRate, "RatedEvaporatorAirFlowRate", "Rated Evaporator Air Flow Rate"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporatorAirInletNodeName, "EvaporatorAirInletNodeName", "Evaporator Air Inlet Node Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporatorAirOutletNodeName, "EvaporatorAirOutletNodeName", "Evaporator Air Outlet Node Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeAvailable, "CoolingOnlyModeAvailable", "Cooling Only Mode Available"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity, "CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity", "Cooling Only Mode Rated Total Evaporator Cooling Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedSensibleHeatRatio, "CoolingOnlyModeRatedSensibleHeatRatio", "Cooling Only Mode Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedCOP, "CoolingOnlyModeRatedCOP", "Cooling Only Mode Rated COP"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName, "CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName", "Cooling Only Mode Total Evaporator Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName, "CoolingOnlyModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName", "Cooling Only Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeEnergyInputRatioFunctionofTemperatureCurveName, "CoolingOnlyModeEnergyInputRatioFunctionofTemperatureCurveName", "Cooling Only Mode Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeEnergyInputRatioFunctionofFlowFractionCurveName, "CoolingOnlyModeEnergyInputRatioFunctionofFlowFractionCurveName", "Cooling Only Mode Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModePartLoadFractionCorrelationCurveName, "CoolingOnlyModePartLoadFractionCorrelationCurveName", "Cooling Only Mode Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeSensibleHeatRatioFunctionofTemperatureCurveName, "CoolingOnlyModeSensibleHeatRatioFunctionofTemperatureCurveName", "Cooling Only Mode Sensible Heat Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeSensibleHeatRatioFunctionofFlowFractionCurveName, "CoolingOnlyModeSensibleHeatRatioFunctionofFlowFractionCurveName", "Cooling Only Mode Sensible Heat Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeAvailable, "CoolingAndChargeModeAvailable", "Cooling And Charge Mode Available"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity, "CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity", "Cooling And Charge Mode Rated Total Evaporator Cooling Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCapacitySizingFactor, "CoolingAndChargeModeCapacitySizingFactor", "Cooling And Charge Mode Capacity Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedStorageChargingCapacity, "CoolingAndChargeModeRatedStorageChargingCapacity", "Cooling And Charge Mode Rated Storage Charging Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageCapacitySizingFactor, "CoolingAndChargeModeStorageCapacitySizingFactor", "Cooling And Charge Mode Storage Capacity Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedSensibleHeatRatio, "CoolingAndChargeModeRatedSensibleHeatRatio", "Cooling And Charge Mode Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCoolingRatedCOP, "CoolingAndChargeModeCoolingRatedCOP", "Cooling And Charge Mode Cooling Rated COP"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeChargingRatedCOP, "CoolingAndChargeModeChargingRatedCOP", "Cooling And Charge Mode Charging Rated COP"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName, "CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName", "Cooling And Charge Mode Total Evaporator Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName, "CoolingAndChargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName", "Cooling And Charge Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurveName, "CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurveName", "Cooling And Charge Mode Evaporator Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurveName, "CoolingAndChargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurveName", "Cooling And Charge Mode Evaporator Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeEvaporatorPartLoadFractionCorrelationCurveName, "CoolingAndChargeModeEvaporatorPartLoadFractionCorrelationCurveName", "Cooling And Charge Mode Evaporator Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageChargeCapacityFunctionofTemperatureCurveName, "CoolingAndChargeModeStorageChargeCapacityFunctionofTemperatureCurveName", "Cooling And Charge Mode Storage Charge Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageChargeCapacityFunctionofTotalEvaporatorPLRCurveName, "CoolingAndChargeModeStorageChargeCapacityFunctionofTotalEvaporatorPLRCurveName", "Cooling And Charge Mode Storage Charge Capacity Function of Total Evaporator PLR Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageEnergyInputRatioFunctionofTemperatureCurveName, "CoolingAndChargeModeStorageEnergyInputRatioFunctionofTemperatureCurveName", "Cooling And Charge Mode Storage Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageEnergyInputRatioFunctionofFlowFractionCurveName, "CoolingAndChargeModeStorageEnergyInputRatioFunctionofFlowFractionCurveName", "Cooling And Charge Mode Storage Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageEnergyPartLoadFractionCorrelationCurveName, "CoolingAndChargeModeStorageEnergyPartLoadFractionCorrelationCurveName", "Cooling And Charge Mode Storage Energy Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeSensibleHeatRatioFunctionofTemperatureCurveName, "CoolingAndChargeModeSensibleHeatRatioFunctionofTemperatureCurveName", "Cooling And Charge Mode Sensible Heat Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeSensibleHeatRatioFunctionofFlowFractionCurveName, "CoolingAndChargeModeSensibleHeatRatioFunctionofFlowFractionCurveName", "Cooling And Charge Mode Sensible Heat Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeAvailable, "CoolingAndDischargeModeAvailable", "Cooling And Discharge Mode Available"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity, "CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity", "Cooling And Discharge Mode Rated Total Evaporator Cooling Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorCapacitySizingFactor, "CoolingAndDischargeModeEvaporatorCapacitySizingFactor", "Cooling And Discharge Mode Evaporator Capacity Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity, "CoolingAndDischargeModeRatedStorageDischargingCapacity", "Cooling And Discharge Mode Rated Storage Discharging Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacitySizingFactor, "CoolingAndDischargeModeStorageDischargeCapacitySizingFactor", "Cooling And Discharge Mode Storage Discharge Capacity Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedSensibleHeatRatio, "CoolingAndDischargeModeRatedSensibleHeatRatio", "Cooling And Discharge Mode Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeCoolingRatedCOP, "CoolingAndDischargeModeCoolingRatedCOP", "Cooling And Discharge Mode Cooling Rated COP"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeDischargingRatedCOP, "CoolingAndDischargeModeDischargingRatedCOP", "Cooling And Discharge Mode Discharging Rated COP"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName, "CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofTemperatureCurveName", "Cooling And Discharge Mode Total Evaporator Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName, "CoolingAndDischargeModeTotalEvaporatorCoolingCapacityFunctionofFlowFractionCurveName", "Cooling And Discharge Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurveName, "CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofTemperatureCurveName", "Cooling And Discharge Mode Evaporator Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurveName, "CoolingAndDischargeModeEvaporatorEnergyInputRatioFunctionofFlowFractionCurveName", "Cooling And Discharge Mode Evaporator Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorPartLoadFractionCorrelationCurveName, "CoolingAndDischargeModeEvaporatorPartLoadFractionCorrelationCurveName", "Cooling And Discharge Mode Evaporator Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacityFunctionofTemperatureCurveName, "CoolingAndDischargeModeStorageDischargeCapacityFunctionofTemperatureCurveName", "Cooling And Discharge Mode Storage Discharge Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacityFunctionofFlowFractionCurveName, "CoolingAndDischargeModeStorageDischargeCapacityFunctionofFlowFractionCurveName", "Cooling And Discharge Mode Storage Discharge Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacityFunctionofTotalEvaporatorPLRCurveName, "CoolingAndDischargeModeStorageDischargeCapacityFunctionofTotalEvaporatorPLRCurveName", "Cooling And Discharge Mode Storage Discharge Capacity Function of Total Evaporator PLR Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageEnergyInputRatioFunctionofTemperatureCurveName, "CoolingAndDischargeModeStorageEnergyInputRatioFunctionofTemperatureCurveName", "Cooling And Discharge Mode Storage Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageEnergyInputRatioFunctionofFlowFractionCurveName, "CoolingAndDischargeModeStorageEnergyInputRatioFunctionofFlowFractionCurveName", "Cooling And Discharge Mode Storage Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageEnergyPartLoadFractionCorrelationCurveName, "CoolingAndDischargeModeStorageEnergyPartLoadFractionCorrelationCurveName", "Cooling And Discharge Mode Storage Energy Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeSensibleHeatRatioFunctionofTemperatureCurveName, "CoolingAndDischargeModeSensibleHeatRatioFunctionofTemperatureCurveName", "Cooling And Discharge Mode Sensible Heat Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeSensibleHeatRatioFunctionofFlowFractionCurveName, "CoolingAndDischargeModeSensibleHeatRatioFunctionofFlowFractionCurveName", "Cooling And Discharge Mode Sensible Heat Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeAvailable, "ChargeOnlyModeAvailable", "Charge Only Mode Available"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity, "ChargeOnlyModeRatedStorageChargingCapacity", "Charge Only Mode Rated Storage Charging Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeCapacitySizingFactor, "ChargeOnlyModeCapacitySizingFactor", "Charge Only Mode Capacity Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeChargingRatedCOP, "ChargeOnlyModeChargingRatedCOP", "Charge Only Mode Charging Rated COP"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeStorageChargeCapacityFunctionofTemperatureCurveName, "ChargeOnlyModeStorageChargeCapacityFunctionofTemperatureCurveName", "Charge Only Mode Storage Charge Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeStorageEnergyInputRatioFunctionofTemperatureCurveName, "ChargeOnlyModeStorageEnergyInputRatioFunctionofTemperatureCurveName", "Charge Only Mode Storage Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeAvailable, "DischargeOnlyModeAvailable", "Discharge Only Mode Available"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedStorageDischargingCapacity, "DischargeOnlyModeRatedStorageDischargingCapacity", "Discharge Only Mode Rated Storage Discharging Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeCapacitySizingFactor, "DischargeOnlyModeCapacitySizingFactor", "Discharge Only Mode Capacity Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedSensibleHeatRatio, "DischargeOnlyModeRatedSensibleHeatRatio", "Discharge Only Mode Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedCOP, "DischargeOnlyModeRatedCOP", "Discharge Only Mode Rated COP"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeStorageDischargeCapacityFunctionofTemperatureCurveName, "DischargeOnlyModeStorageDischargeCapacityFunctionofTemperatureCurveName", "Discharge Only Mode Storage Discharge Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeStorageDischargeCapacityFunctionofFlowFractionCurveName, "DischargeOnlyModeStorageDischargeCapacityFunctionofFlowFractionCurveName", "Discharge Only Mode Storage Discharge Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeEnergyInputRatioFunctionofTemperatureCurveName, "DischargeOnlyModeEnergyInputRatioFunctionofTemperatureCurveName", "Discharge Only Mode Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeEnergyInputRatioFunctionofFlowFractionCurveName, "DischargeOnlyModeEnergyInputRatioFunctionofFlowFractionCurveName", "Discharge Only Mode Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModePartLoadFractionCorrelationCurveName, "DischargeOnlyModePartLoadFractionCorrelationCurveName", "Discharge Only Mode Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeSensibleHeatRatioFunctionofTemperatureCurveName, "DischargeOnlyModeSensibleHeatRatioFunctionofTemperatureCurveName", "Discharge Only Mode Sensible Heat Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeSensibleHeatRatioFunctionofFlowFractionCurveName, "DischargeOnlyModeSensibleHeatRatioFunctionofFlowFractionCurveName", "Discharge Only Mode Sensible Heat Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AncillaryElectricPower, "AncillaryElectricPower", "Ancillary Electric Power"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationMinimumOutdoorAirTemperature, "ColdWeatherOperationMinimumOutdoorAirTemperature", "Cold Weather Operation Minimum Outdoor Air Temperature"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationAncillaryPower, "ColdWeatherOperationAncillaryPower", "Cold Weather Operation Ancillary Power"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirOutletNodeName, "CondenserAirOutletNodeName", "Condenser Air Outlet Node Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserDesignAirFlowRate, "CondenserDesignAirFlowRate", "Condenser Design Air Flow Rate"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirFlowSizingFactor, "CondenserAirFlowSizingFactor", "Condenser Air Flow Sizing Factor"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserType, "CondenserType", "Condenser Type"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterAvailabilityScheduleName, "BasinHeaterAvailabilityScheduleName", "Basin Heater Availability Schedule Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionInletNodeName, "StorageTankPlantConnectionInletNodeName", "Storage Tank Plant Connection Inlet Node Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionOutletNodeName, "StorageTankPlantConnectionOutletNodeName", "Storage Tank Plant Connection Outlet Node Name"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionDesignFlowRate, "StorageTankPlantConnectionDesignFlowRate", "Storage Tank Plant Connection Design Flow Rate"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankPlantConnectionHeatTransferEffectiveness, "StorageTankPlantConnectionHeatTransferEffectiveness", "Storage Tank Plant Connection Heat Transfer Effectiveness"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankMinimumOperatingLimitFluidTemperature, "StorageTankMinimumOperatingLimitFluidTemperature", "Storage Tank Minimum Operating Limit Fluid Temperature"},
{ Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTankMaximumOperatingLimitFluidTemperature, "StorageTankMaximumOperatingLimitFluidTemperature", "Storage Tank Maximum Operating Limit Fluid Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_SingleSpeed_ThermalStorageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_SingleSpeed_ThermalStorageFields> OptionalCoil_Cooling_DX_SingleSpeed_ThermalStorageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_SINGLESPEED_THERMALSTORAGE_FIELDENUMS_HXX

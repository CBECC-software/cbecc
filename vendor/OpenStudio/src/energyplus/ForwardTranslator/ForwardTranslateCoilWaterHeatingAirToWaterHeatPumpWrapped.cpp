/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#include "../ForwardTranslator.hpp"
#include "../../model/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "../../model/CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"
#include "../../model/Model.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/Curve.hpp"
#include "../../model/Curve_Impl.hpp"
#include "../../utilities/core/Assert.hpp"
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Wrapped_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;
using namespace std;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject>
    ForwardTranslator::translateCoilWaterHeatingAirToWaterHeatPumpWrapped(CoilWaterHeatingAirToWaterHeatPumpWrapped& modelObject) {
    IdfObject idfObject(IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Wrapped);
    m_idfObjects.push_back(idfObject);

    // Name
    if (auto s = modelObject.name()) {
      idfObject.setName(*s);
    }

    //double ratedHeatingCapacity() const;
    //double ratedCOP() const;
    //double ratedSensibleHeatRatio() const;
    //double ratedEvaporatorInletAirDryBulbTemperature() const;
    //double ratedEvaporatorInletAirWetBulbTemperature() const;
    //double ratedCondenserWaterTemperature() const;
    //boost::optional<double> ratedEvaporatorAirFlowRate() const;
    //bool isRatedEvaporatorAirFlowRateAutocalculated() const;
    //bool evaporatorFanPowerIncludedinRatedCOP() const;
    //double crankcaseHeaterCapacity() const;
    //double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
    //std::string evaporatorAirTemperatureTypeforCurveObjects() const;
    //Curve heatingCapacityFunctionofTemperatureCurve() const;
    //Curve heatingCapacityFunctionofAirFlowFractionCurve() const;
    //Curve heatingCOPFunctionofTemperatureCurve() const;
    //Curve heatingCOPFunctionofAirFlowFractionCurve() const;
    //Curve partLoadFractionCorrelationCurve() const;

    //{ Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::Name, "Name", "Name"},
    //{ Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedHeatingCapacity, "RatedHeatingCapacity", "Rated Heating Capacity"},
    {
      auto value = modelObject.ratedHeatingCapacity();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedHeatingCapacity, value);
    }

    {
      auto value = modelObject.ratedCOP();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCOP, value);
    }

    {
      auto value = modelObject.ratedSensibleHeatRatio();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedSensibleHeatRatio, value);
    }

    {
      auto value = modelObject.ratedEvaporatorInletAirDryBulbTemperature();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirDryBulbTemperature, value);
    }

    {
      auto value = modelObject.ratedEvaporatorInletAirWetBulbTemperature();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirWetBulbTemperature, value);
    }

    {
      auto value = modelObject.ratedCondenserWaterTemperature();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCondenserWaterTemperature, value);
    }

    if (modelObject.isRatedEvaporatorAirFlowRateAutocalculated()) {
      idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, "Autocalculate");
    } else if (auto value = modelObject.ratedEvaporatorAirFlowRate()) {
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, value.get());
    }

    {
      if (modelObject.evaporatorFanPowerIncludedinRatedCOP()) {
        idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorFanPowerIncludedinRatedCOP, "Yes");
      } else {
        idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorFanPowerIncludedinRatedCOP, "No");
      }
    }

    {
      auto value = modelObject.crankcaseHeaterCapacity();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacity, value);
    }

    {
      auto value = modelObject.maximumAmbientTemperatureforCrankcaseHeaterOperation();
      idfObject.setDouble(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, value);
    }

    {
      auto value = modelObject.evaporatorAirTemperatureTypeforCurveObjects();
      idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirTemperatureTypeforCurveObjects, value);
    }

    {
      auto curve = modelObject.heatingCapacityFunctionofTemperatureCurve();
      if (auto idf = translateAndMapModelObject(curve)) {
        idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofTemperatureCurveName, idf->name().get());
      }
    }

    {
      auto curve = modelObject.heatingCapacityFunctionofAirFlowFractionCurve();
      if (auto idf = translateAndMapModelObject(curve)) {
        idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofAirFlowFractionCurveName, idf->name().get());
      }
    }

    {
      auto curve = modelObject.heatingCOPFunctionofTemperatureCurve();
      if (auto idf = translateAndMapModelObject(curve)) {
        idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofTemperatureCurveName, idf->name().get());
      }
    }

    {
      auto curve = modelObject.heatingCOPFunctionofAirFlowFractionCurve();
      if (auto idf = translateAndMapModelObject(curve)) {
        idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofAirFlowFractionCurveName, idf->name().get());
      }
    }

    {
      auto curve = modelObject.partLoadFractionCorrelationCurve();
      if (auto idf = translateAndMapModelObject(curve)) {
        idfObject.setString(Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::PartLoadFractionCorrelationCurveName, idf->name().get());
      }
    }

    return idfObject;
  }

}  // namespace energyplus
}  // namespace openstudio

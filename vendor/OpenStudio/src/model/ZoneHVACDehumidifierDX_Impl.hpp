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

#ifndef MODEL_ZONEHVACDEHUMIDIFIERDX_IMPL_HPP
#define MODEL_ZONEHVACDEHUMIDIFIERDX_IMPL_HPP

#include "ModelAPI.hpp"
#include "ZoneHVACComponent_Impl.hpp"

namespace openstudio {
namespace model {

  class Schedule;
  class Curve;
  // class WaterStorageTank;

  namespace detail {

    /** ZoneHVACDehumidifierDX_Impl is a ZoneHVACComponent_Impl that is the implementation class for ZoneHVACDehumidifierDX.*/
    class MODEL_API ZoneHVACDehumidifierDX_Impl : public ZoneHVACComponent_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      ZoneHVACDehumidifierDX_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      ZoneHVACDehumidifierDX_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      ZoneHVACDehumidifierDX_Impl(const ZoneHVACDehumidifierDX_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~ZoneHVACDehumidifierDX_Impl() {}

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

      virtual std::vector<ModelObject> children() const override;

      virtual unsigned inletPort() const override;

      virtual unsigned outletPort() const override;

      //@}
      /** @name Getters */
      //@{

      Schedule availabilitySchedule() const;

      double ratedWaterRemoval() const;

      double ratedEnergyFactor() const;

      double ratedAirFlowRate() const;

      Curve waterRemovalCurve() const;

      Curve energyFactorCurve() const;

      Curve partLoadFractionCorrelationCurve() const;

      double minimumDryBulbTemperatureforDehumidifierOperation() const;

      double maximumDryBulbTemperatureforDehumidifierOperation() const;

      double offCycleParasiticElectricLoad() const;

      // boost::optional<WaterStorageTank> condensateCollectionWaterStorageTank() const;

      //@}
      /** @name Setters */
      //@{

      bool setAvailabilitySchedule(Schedule& schedule);

      bool setRatedWaterRemoval(double ratedWaterRemoval);

      bool setRatedEnergyFactor(double ratedEnergyFactor);

      bool setRatedAirFlowRate(double ratedAirFlowRate);

      bool setWaterRemovalCurve(const Curve& curve);

      bool setEnergyFactorCurve(const Curve& curve);

      bool setPartLoadFractionCorrelationCurve(const Curve& curve);

      bool setMinimumDryBulbTemperatureforDehumidifierOperation(double minimumDryBulbTemperatureforDehumidifierOperation);

      bool setMaximumDryBulbTemperatureforDehumidifierOperation(double maximumDryBulbTemperatureforDehumidifierOperation);

      bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);

      // bool setCondensateCollectionWaterStorageTank(const boost::optional<WaterStorageTank>& waterStorageTank);

      // void resetCondensateCollectionWaterStorageTank();

      //@}
      /** @name Other */
      //@{

      ModelObject clone(Model model) const override;

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.ZoneHVACDehumidifierDX");

      // Optional getters for use by methods like children() so can remove() if the constructor fails.
      // There are other ways for the public versions of these getters to fail--perhaps all required
      // objects should be returned as boost::optionals
      boost::optional<Schedule> optionalAvailabilitySchedule() const;
      boost::optional<Curve> optionalWaterRemovalCurve() const;
      boost::optional<Curve> optionalEnergyFactorCurve() const;
      boost::optional<Curve> optionalPartLoadFractionCorrelationCurve() const;
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_ZONEHVACDEHUMIDIFIERDX_IMPL_HPP

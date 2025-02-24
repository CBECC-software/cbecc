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

#ifndef MODEL_SHADOWCALCULATION_IMPL_HPP
#define MODEL_SHADOWCALCULATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace model {

  class ThermalZone;
  class ModelObjectList;

  namespace detail {

    class MODEL_API ShadowCalculation_Impl : public ModelObject_Impl
    {

     public:
      // constructor
      ShadowCalculation_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      // construct from workspace
      ShadowCalculation_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      // clone copy constructor
      ShadowCalculation_Impl(const ShadowCalculation_Impl& other, Model_Impl* model, bool keepHandle);

      // virtual destructor
      virtual ~ShadowCalculation_Impl() {}

      // return the parent object in the hierarchy
      virtual boost::optional<ParentObject> parent() const override;

      // set the parent, child may have to call methods on the parent
      virtual bool setParent(ParentObject& newParent) override;

      // Get all output variable names that could be associated with this object.
      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      /** @name Getters */
      //@{

      std::string shadingCalculationMethod() const;

      std::string shadingCalculationUpdateFrequencyMethod() const;
      bool isShadingCalculationUpdateFrequencyMethodDefaulted() const;

      int shadingCalculationUpdateFrequency() const;
      bool isShadingCalculationUpdateFrequencyDefaulted() const;

      int maximumFiguresInShadowOverlapCalculations() const;
      bool isMaximumFiguresInShadowOverlapCalculationsDefaulted() const;

      std::string polygonClippingAlgorithm() const;

      int pixelCountingResolution() const;

      std::string skyDiffuseModelingAlgorithm() const;

      bool outputExternalShadingCalculationResults() const;

      bool disableSelfShadingWithinShadingZoneGroups() const;

      bool disableSelfShadingFromShadingZoneGroupstoOtherZones() const;

      unsigned int numberofShadingZoneGroups() const;
      std::vector<ThermalZone> getShadingZoneGroup(unsigned groupIndex) const;

      //@}
      /** @name Setters */
      //@{

      bool setShadingCalculationMethod(const std::string& shadingCalculationMethod);

      bool setShadingCalculationUpdateFrequencyMethod(const std::string& shadingCalculationUpdateFrequencyMethod);
      void resetShadingCalculationUpdateFrequencyMethod();

      bool setShadingCalculationUpdateFrequency(int shadingCalculationUpdateFrequency);
      void resetShadingCalculationUpdateFrequency();

      bool setMaximumFiguresInShadowOverlapCalculations(int maximumFiguresInShadowOverlapCalculations);
      void resetMaximumFiguresInShadowOverlapCalculations();

      bool setPolygonClippingAlgorithm(const std::string& polygonClippingAlgorithm);
      void resetPolygonClippingAlgorithm();

      bool setPixelCountingResolution(int pixelCountingResolution);

      bool setSkyDiffuseModelingAlgorithm(const std::string& skyDiffuseModelingAlgorithm);
      void resetSkyDiffuseModelingAlgorithm();

      bool setOutputExternalShadingCalculationResults(bool outputExternalShadingCalculationResults);

      bool setDisableSelfShadingWithinShadingZoneGroups(bool disableSelfShadingWithinShadingZoneGroups);

      bool setDisableSelfShadingFromShadingZoneGroupstoOtherZones(bool disableSelfShadingFromShadingZoneGroupstoOtherZones);

      bool addShadingZoneGroup(const std::vector<ThermalZone>& thermalZones);
      bool removeShadingZoneGroup(unsigned groupIndex);
      void removeAllShadingZoneGroups();

      //@}

     private:
      REGISTER_LOGGER("openstudio.model.ShadowCalculation");

      boost::optional<ModelObjectList> getShadingZoneGroupModelObjectList(unsigned groupIndex) const;
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_SHADOWCALCULATION_IMPL_HPP

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

#include "AirflowNetworkFan.hpp"
#include "AirflowNetworkFan_Impl.hpp"

#include "FanConstantVolume.hpp"
#include "FanConstantVolume_Impl.hpp"
#include "FanVariableVolume.hpp"
#include "FanVariableVolume_Impl.hpp"
#include "FanOnOff.hpp"
#include "FanOnOff_Impl.hpp"
#include "FanSystemModel.hpp"
#include "FanSystemModel_Impl.hpp"
#include "StraightComponent.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_AirflowNetworkFan_FieldEnums.hxx>

#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    AirflowNetworkFan_Impl::AirflowNetworkFan_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : AirflowNetworkComponent_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == AirflowNetworkFan::iddObjectType());
    }

    AirflowNetworkFan_Impl::AirflowNetworkFan_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : AirflowNetworkComponent_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == AirflowNetworkFan::iddObjectType());
    }

    AirflowNetworkFan_Impl::AirflowNetworkFan_Impl(const AirflowNetworkFan_Impl& other, Model_Impl* model, bool keepHandle)
      : AirflowNetworkComponent_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& AirflowNetworkFan_Impl::outputVariableNames() const {
      static const std::vector<std::string> result;
      return result;
    }

    IddObjectType AirflowNetworkFan_Impl::iddObjectType() const {
      return AirflowNetworkFan::iddObjectType();
    }

    boost::optional<FanConstantVolume> AirflowNetworkFan_Impl::fanConstantVolume() const {
      return getObject<ModelObject>().getModelObjectTarget<FanConstantVolume>(OS_AirflowNetworkFanFields::FanName);
    }

    boost::optional<FanVariableVolume> AirflowNetworkFan_Impl::fanVariableVolume() const {
      return getObject<ModelObject>().getModelObjectTarget<FanVariableVolume>(OS_AirflowNetworkFanFields::FanName);
    }

    boost::optional<FanOnOff> AirflowNetworkFan_Impl::fanOnOff() const {
      return getObject<ModelObject>().getModelObjectTarget<FanOnOff>(OS_AirflowNetworkFanFields::FanName);
    }

    boost::optional<FanSystemModel> AirflowNetworkFan_Impl::fanSystemModel() const {
      return getObject<ModelObject>().getModelObjectTarget<FanSystemModel>(OS_AirflowNetworkFanFields::FanName);
    }

    boost::optional<ModelObject> AirflowNetworkFan_Impl::componentModelObject() const {
      return getObject<ModelObject>().getModelObjectTarget<ModelObject>(OS_AirflowNetworkFanFields::FanName);
    }

    void AirflowNetworkFan_Impl::resetFan() {
      bool result = setString(OS_AirflowNetworkFanFields::FanName, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  AirflowNetworkFan::AirflowNetworkFan(const Model& model, const Handle& handle)
    : AirflowNetworkComponent(AirflowNetworkFan::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::AirflowNetworkFan_Impl>());
    bool ok = getImpl<detail::AirflowNetworkFan_Impl>()->setPointer(OS_AirflowNetworkFanFields::FanName, handle);
    OS_ASSERT(ok);
  }

  IddObjectType AirflowNetworkFan::iddObjectType() {
    return IddObjectType(IddObjectType::OS_AirflowNetworkFan);
  }

  boost::optional<FanConstantVolume> AirflowNetworkFan::fanConstantVolume() const {
    return getImpl<detail::AirflowNetworkFan_Impl>()->fanConstantVolume();
  }

  boost::optional<FanVariableVolume> AirflowNetworkFan::fanVariableVolume() const {
    return getImpl<detail::AirflowNetworkFan_Impl>()->fanVariableVolume();
  }

  boost::optional<FanOnOff> AirflowNetworkFan::fanOnOff() const {
    return getImpl<detail::AirflowNetworkFan_Impl>()->fanOnOff();
  }

  boost::optional<FanSystemModel> AirflowNetworkFan::fanSystemModel() const {
    return getImpl<detail::AirflowNetworkFan_Impl>()->fanSystemModel();
  }

  void AirflowNetworkFan::resetFan() {
    getImpl<detail::AirflowNetworkFan_Impl>()->resetFan();
  }

  /// @cond
  AirflowNetworkFan::AirflowNetworkFan(std::shared_ptr<detail::AirflowNetworkFan_Impl> impl) : AirflowNetworkComponent(impl) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio

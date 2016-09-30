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

#include "ComponentCostAdjustments.hpp"
#include "ComponentCostAdjustments_Impl.hpp"

#include "Model_Impl.hpp"

#include <utilities/idd/OS_ComponentCost_Adjustments_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include "../utilities/core/Assert.hpp"

#include <boost/algorithm/string.hpp>

namespace openstudio {
namespace model  {
namespace detail {

ComponentCostAdjustments_Impl::ComponentCostAdjustments_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
  : ParentObject_Impl(idfObject, model, keepHandle)
{
  OS_ASSERT(idfObject.iddObject().type() == ComponentCostAdjustments::iddObjectType());
}

ComponentCostAdjustments_Impl::ComponentCostAdjustments_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                           Model_Impl* model,
                                           bool keepHandle)
  : ParentObject_Impl(other,model,keepHandle)
{
  OS_ASSERT(other.iddObject().type() == ComponentCostAdjustments::iddObjectType());
}

ComponentCostAdjustments_Impl::ComponentCostAdjustments_Impl(const ComponentCostAdjustments_Impl& other,Model_Impl* model,bool keepHandle)
  : ParentObject_Impl(other,model,keepHandle)
{
}

OptionalDouble ComponentCostAdjustments_Impl::miscellaneousCostPerConditionedArea() const
{
  return getDouble(OS_ComponentCost_AdjustmentsFields::MiscellaneousCostperConditionedArea);
}

void ComponentCostAdjustments_Impl::setMiscellaneousCostPerConditionedArea(double num)
{
  setDouble(OS_ComponentCost_AdjustmentsFields::MiscellaneousCostperConditionedArea,num);
}

OptionalDouble ComponentCostAdjustments_Impl::designAndEngineeringFees() const
{
  return getDouble(OS_ComponentCost_AdjustmentsFields::DesignandEngineeringFees);
}

void ComponentCostAdjustments_Impl::setDesignAndEngineeringFees(double num)
{
  setDouble(OS_ComponentCost_AdjustmentsFields::DesignandEngineeringFees,num);
}

OptionalDouble ComponentCostAdjustments_Impl::contractorFee() const
{
  return getDouble(OS_ComponentCost_AdjustmentsFields::ContractorFee);
}

void ComponentCostAdjustments_Impl::setContractorFee(double num)
{
  setDouble(OS_ComponentCost_AdjustmentsFields::ContractorFee,num);
}

OptionalDouble ComponentCostAdjustments_Impl::contingency() const
{
  return getDouble(OS_ComponentCost_AdjustmentsFields::Contingency);
}

void ComponentCostAdjustments_Impl::setContingency(double num)
{
  setDouble(OS_ComponentCost_AdjustmentsFields::Contingency,num);
}

OptionalDouble ComponentCostAdjustments_Impl::permitsBondingAndInsurance() const
{
  return getDouble(OS_ComponentCost_AdjustmentsFields::PermitsBondingandInsurance);
}

void ComponentCostAdjustments_Impl::setPermitsBondingAndInsurance(double num)
{
  setDouble(OS_ComponentCost_AdjustmentsFields::PermitsBondingandInsurance,num);
}

OptionalDouble ComponentCostAdjustments_Impl::commissioningFee() const
{
  return getDouble(OS_ComponentCost_AdjustmentsFields::CommissioningFee);
}

void ComponentCostAdjustments_Impl::setCommissioningFee(double num)
{
  setDouble(OS_ComponentCost_AdjustmentsFields::CommissioningFee,num);
}

OptionalDouble ComponentCostAdjustments_Impl::regionalAdjustmentFactor() const
{
  return getDouble(OS_ComponentCost_AdjustmentsFields::RegionalAdjustmentFactor);
}

void ComponentCostAdjustments_Impl::setRegionalAdjustmentFactor(double num)
{
  setDouble(OS_ComponentCost_AdjustmentsFields::RegionalAdjustmentFactor,num);
}

// return the parent object in the hierarchy
boost::optional<ParentObject> ComponentCostAdjustments_Impl::parent() const
{
  return boost::optional<ParentObject>();
}

// set the parent, child may have to call methods on the parent
bool ComponentCostAdjustments_Impl::setParent(ParentObject& newParent)
{
  //if (newParent.optionalCast<SomeParentClass>() && (newParent.model() == model())) {
  //  return true;
  //}
  return false;
}

// return any children objects in the hierarchy
std::vector<ModelObject> ComponentCostAdjustments_Impl::children() const
{
  std::vector<ModelObject> result;
  return result;
}

std::vector<IddObjectType> ComponentCostAdjustments_Impl::allowableChildTypes() const {
  IddObjectTypeVector result;
  return result;
}

// Get all output variable names that could be associated with this object.
const std::vector<std::string>& ComponentCostAdjustments_Impl::outputVariableNames() const
{
  static std::vector<std::string> result;
  if (result.empty()){
  }
  return result;
}

} // detail

/// constructor
ComponentCostAdjustments::ComponentCostAdjustments(const Model& model)
  : ParentObject(ComponentCostAdjustments::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::ComponentCostAdjustments_Impl>());
}

// constructor
ComponentCostAdjustments::ComponentCostAdjustments(std::shared_ptr<detail::ComponentCostAdjustments_Impl> impl)
  : ParentObject(impl)
{}

OptionalDouble ComponentCostAdjustments::miscellaneousCostPerConditionedArea() const
{
  return getImpl<detail::ComponentCostAdjustments_Impl>()->miscellaneousCostPerConditionedArea();
}

void ComponentCostAdjustments::setMiscellaneousCostPerConditionedArea(double num)
{
  getImpl<detail::ComponentCostAdjustments_Impl>()->setMiscellaneousCostPerConditionedArea(num);
}

OptionalDouble ComponentCostAdjustments::designAndEngineeringFees() const
{
  return getImpl<detail::ComponentCostAdjustments_Impl>()->designAndEngineeringFees();
}

void ComponentCostAdjustments::setDesignAndEngineeringFees(double num)
{
  getImpl<detail::ComponentCostAdjustments_Impl>()->setDesignAndEngineeringFees(num);
}

OptionalDouble ComponentCostAdjustments::contractorFee() const
{
  return getImpl<detail::ComponentCostAdjustments_Impl>()->contractorFee();
}

void ComponentCostAdjustments::setContractorFee(double num)
{
  getImpl<detail::ComponentCostAdjustments_Impl>()->setContractorFee(num);
}

OptionalDouble ComponentCostAdjustments::contingency() const
{
  return getImpl<detail::ComponentCostAdjustments_Impl>()->contingency();
}

void ComponentCostAdjustments::setContingency(double num)
{
  getImpl<detail::ComponentCostAdjustments_Impl>()->setContingency(num);
}

OptionalDouble ComponentCostAdjustments::permitsBondingAndInsurance() const
{
  return getImpl<detail::ComponentCostAdjustments_Impl>()->permitsBondingAndInsurance();
}

void ComponentCostAdjustments::setPermitsBondingAndInsurance(double num)
{
  getImpl<detail::ComponentCostAdjustments_Impl>()->setPermitsBondingAndInsurance(num);
}

OptionalDouble ComponentCostAdjustments::commissioningFee() const
{
  return getImpl<detail::ComponentCostAdjustments_Impl>()->commissioningFee();
}

void ComponentCostAdjustments::setCommissioningFee(double num)
{
  getImpl<detail::ComponentCostAdjustments_Impl>()->setCommissioningFee(num);
}

OptionalDouble ComponentCostAdjustments::regionalAdjustmentFactor() const
{
  return getImpl<detail::ComponentCostAdjustments_Impl>()->regionalAdjustmentFactor();
}

void ComponentCostAdjustments::setRegionalAdjustmentFactor(double num)
{
  getImpl<detail::ComponentCostAdjustments_Impl>()->setRegionalAdjustmentFactor(num);
}

IddObjectType ComponentCostAdjustments::iddObjectType()
{
  IddObjectType result(IddObjectType::OS_ComponentCost_Adjustments);
  return result;
}

} // model
} // openstudio

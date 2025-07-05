/**********************************************************************
 *  Copyright (c) 2008-2013, Alliance for Sustainable Energy.
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

#include <model/LifeCycleCostNonrecurringCost.hpp>
#include <model/LifeCycleCostNonrecurringCost_Impl.hpp>

#include <model/Model_Impl.hpp>

#include <utilities/idd/OS_LifeCycleCost_NonrecurringCost_FieldEnums.hxx>

#include <utilities/core/Assert.hpp>

#include <boost/algorithm/string.hpp>

namespace openstudio {
namespace model  {
namespace detail {

LifeCycleCostNonrecurringCost_Impl::LifeCycleCostNonrecurringCost_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
  : ParentObject_Impl(idfObject, model, keepHandle)
{
  BOOST_ASSERT(idfObject.iddObject().type() == LifeCycleCostNonrecurringCost::iddObjectType());
}

LifeCycleCostNonrecurringCost_Impl::LifeCycleCostNonrecurringCost_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                           Model_Impl* model,
                                           bool keepHandle)
  : ParentObject_Impl(other,model,keepHandle)
{
  BOOST_ASSERT(other.iddObject().type() == LifeCycleCostNonrecurringCost::iddObjectType());
}

LifeCycleCostNonrecurringCost_Impl::LifeCycleCostNonrecurringCost_Impl(const LifeCycleCostNonrecurringCost_Impl& other,Model_Impl* model,bool keepHandle)
  : ParentObject_Impl(other,model,keepHandle)
{
}

OptionalInt LifeCycleCostNonrecurringCost_Impl::yearsFromStart() const
{
  return getInt(OS_LifeCycleCost_NonrecurringCostFields::YearsfromStart);
}

void LifeCycleCostNonrecurringCost_Impl::setYearsFromStart(int num)
{
  setInt(OS_LifeCycleCost_NonrecurringCostFields::YearsfromStart,num);
}

OptionalInt LifeCycleCostNonrecurringCost_Impl::monthsFromStart() const
{
  return getInt(OS_LifeCycleCost_NonrecurringCostFields::MonthsfromStart);
}

void LifeCycleCostNonrecurringCost_Impl::setMonthsFromStart(int num)
{
  setInt(OS_LifeCycleCost_NonrecurringCostFields::MonthsfromStart,num);
}

OptionalDouble LifeCycleCostNonrecurringCost_Impl::cost() const
{
  return getDouble(OS_LifeCycleCost_NonrecurringCostFields::Cost);
}

void LifeCycleCostNonrecurringCost_Impl::setCost(double num)
{
  setDouble(OS_LifeCycleCost_NonrecurringCostFields::Cost,num);
}

OptionalString LifeCycleCostNonrecurringCost_Impl::category() const
{
  return getString(OS_LifeCycleCost_NonrecurringCostFields::Category);
}

void LifeCycleCostNonrecurringCost_Impl::setCategory(const std::string& str)
{
  setString(OS_LifeCycleCost_NonrecurringCostFields::Category,str);
}

OptionalString LifeCycleCostNonrecurringCost_Impl::startOfCosts() const
{
  return getString(OS_LifeCycleCost_NonrecurringCostFields::StartofCosts);
}

void LifeCycleCostNonrecurringCost_Impl::setStartOfCosts(const std::string& str)
{
  setString(OS_LifeCycleCost_NonrecurringCostFields::StartofCosts,str);
}

// return the parent object in the hierarchy
boost::optional<ParentObject> LifeCycleCostNonrecurringCost_Impl::parent() const
{
  return boost::optional<ParentObject>();
}

// set the parent, child may have to call methods on the parent
bool LifeCycleCostNonrecurringCost_Impl::setParent(ParentObject& newParent)
{
  //if (newParent.optionalCast<SomeParentClass>() && (newParent.model() == model())) {
  //  return true;
  //}
  return false;
}

// return any children objects in the hierarchy
std::vector<ModelObject> LifeCycleCostNonrecurringCost_Impl::children() const
{
  std::vector<ModelObject> result;
  return result;
}

std::vector<IddObjectType> LifeCycleCostNonrecurringCost_Impl::allowableChildTypes() const {
  IddObjectTypeVector result;
  return result;
}

// Get all output variable names that could be associated with this object.
const std::vector<std::string>& LifeCycleCostNonrecurringCost_Impl::outputVariableNames() const
{
  static std::vector<std::string> result;
  if (result.empty()){
  }
  return result;
}

} // detail

/// constructor
LifeCycleCostNonrecurringCost::LifeCycleCostNonrecurringCost(const Model& model)
  : ParentObject(LifeCycleCostNonrecurringCost::iddObjectType(),model)
{
  BOOST_ASSERT(getImpl<detail::LifeCycleCostNonrecurringCost_Impl>());
}

// constructor
LifeCycleCostNonrecurringCost::LifeCycleCostNonrecurringCost(boost::shared_ptr<detail::LifeCycleCostNonrecurringCost_Impl> impl)
  : ParentObject(impl)
{}

OptionalInt LifeCycleCostNonrecurringCost::yearsFromStart() const
{
  return getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->yearsFromStart();
}

void LifeCycleCostNonrecurringCost::setYearsFromStart(int num)
{
  getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->setYearsFromStart(num);
}

OptionalInt LifeCycleCostNonrecurringCost::monthsFromStart() const
{
  return getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->monthsFromStart();
}

void LifeCycleCostNonrecurringCost::setMonthsFromStart(int num)
{
  getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->setMonthsFromStart(num);
}

OptionalDouble LifeCycleCostNonrecurringCost::cost() const
{
  return getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->cost();
}

void LifeCycleCostNonrecurringCost::setCost(double num)
{
  getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->setCost(num);
}

OptionalString LifeCycleCostNonrecurringCost::name() const
{
  return getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->name();
}

void LifeCycleCostNonrecurringCost::setName(const std::string& str)
{
  getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->setName(str);
}

OptionalString LifeCycleCostNonrecurringCost::category() const
{
  return getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->category();
}

void LifeCycleCostNonrecurringCost::setCategory(const std::string& str)
{
  getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->setCategory(str);
}

OptionalString LifeCycleCostNonrecurringCost::startOfCosts() const
{
  return getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->startOfCosts();
}

void LifeCycleCostNonrecurringCost::setStartOfCosts(const std::string& str)
{
  getImpl<detail::LifeCycleCostNonrecurringCost_Impl>()->setStartOfCosts(str);
}

IddObjectType LifeCycleCostNonrecurringCost::iddObjectType()
{
  IddObjectType result(IddObjectType::OS_LifeCycleCost_NonrecurringCost);
  return result;
}

} // model
} // openstudio

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

#include <model/LifeCycleCostRecurringCosts.hpp>
#include <model/LifeCycleCostRecurringCosts_Impl.hpp>

#include <model/Model_Impl.hpp>

#include <utilities/idd/OS_LifeCycleCost_RecurringCosts_FieldEnums.hxx>

#include <utilities/core/Assert.hpp>

#include <boost/algorithm/string.hpp>

namespace openstudio {
namespace model  {
namespace detail {

LifeCycleCostRecurringCosts_Impl::LifeCycleCostRecurringCosts_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
  : ParentObject_Impl(idfObject, model, keepHandle)
{
  BOOST_ASSERT(idfObject.iddObject().type() == LifeCycleCostRecurringCosts::iddObjectType());
}

LifeCycleCostRecurringCosts_Impl::LifeCycleCostRecurringCosts_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                           Model_Impl* model,
                                           bool keepHandle)
  : ParentObject_Impl(other,model,keepHandle)
{
  BOOST_ASSERT(other.iddObject().type() == LifeCycleCostRecurringCosts::iddObjectType());
}

LifeCycleCostRecurringCosts_Impl::LifeCycleCostRecurringCosts_Impl(const LifeCycleCostRecurringCosts_Impl& other,Model_Impl* model,bool keepHandle)
  : ParentObject_Impl(other,model,keepHandle)
{
}

OptionalInt LifeCycleCostRecurringCosts_Impl::yearsFromStart() const
{
  return getInt(OS_LifeCycleCost_RecurringCostsFields::YearsfromStart);
}

void LifeCycleCostRecurringCosts_Impl::setYearsFromStart(int num)
{
  setInt(OS_LifeCycleCost_RecurringCostsFields::YearsfromStart,num);
}

OptionalInt LifeCycleCostRecurringCosts_Impl::monthsFromStart() const
{
  return getInt(OS_LifeCycleCost_RecurringCostsFields::MonthsfromStart);
}

void LifeCycleCostRecurringCosts_Impl::setMonthsFromStart(int num)
{
  setInt(OS_LifeCycleCost_RecurringCostsFields::MonthsfromStart,num);
}

OptionalInt LifeCycleCostRecurringCosts_Impl::repeatPeriodYears() const
{
  return getInt(OS_LifeCycleCost_RecurringCostsFields::RepeatPeriodYears);
}

void LifeCycleCostRecurringCosts_Impl::setRepeatPeriodYears(int num)
{
  setInt(OS_LifeCycleCost_RecurringCostsFields::RepeatPeriodYears,num);
}

OptionalInt LifeCycleCostRecurringCosts_Impl::repeatPeriodMonths() const
{
  return getInt(OS_LifeCycleCost_RecurringCostsFields::RepeatPeriodMonths);
}

void LifeCycleCostRecurringCosts_Impl::setRepeatPeriodMonths(int num)
{
  setInt(OS_LifeCycleCost_RecurringCostsFields::RepeatPeriodMonths,num);
}

OptionalDouble LifeCycleCostRecurringCosts_Impl::cost() const
{
  return getDouble(OS_LifeCycleCost_RecurringCostsFields::Cost);
}

void LifeCycleCostRecurringCosts_Impl::setCost(double num)
{
  setDouble(OS_LifeCycleCost_RecurringCostsFields::Cost,num);
}

OptionalDouble LifeCycleCostRecurringCosts_Impl::annualEscalationRate() const
{
  return getDouble(OS_LifeCycleCost_RecurringCostsFields::Annualescalationrate);
}

void LifeCycleCostRecurringCosts_Impl::setAnnualEscalationRate(double num)
{
  setDouble(OS_LifeCycleCost_RecurringCostsFields::Annualescalationrate,num);
}

OptionalString LifeCycleCostRecurringCosts_Impl::category() const
{
  return getString(OS_LifeCycleCost_RecurringCostsFields::Category);
}

void LifeCycleCostRecurringCosts_Impl::setCategory(const std::string& str)
{
  setString(OS_LifeCycleCost_RecurringCostsFields::Category,str);
}

OptionalString LifeCycleCostRecurringCosts_Impl::startOfCosts() const
{
  return getString(OS_LifeCycleCost_RecurringCostsFields::StartofCosts);
}

void LifeCycleCostRecurringCosts_Impl::setStartOfCosts(const std::string& str)
{
  setString(OS_LifeCycleCost_RecurringCostsFields::StartofCosts,str);
}

// return the parent object in the hierarchy
boost::optional<ParentObject> LifeCycleCostRecurringCosts_Impl::parent() const
{
  return boost::optional<ParentObject>();
}

// set the parent, child may have to call methods on the parent
bool LifeCycleCostRecurringCosts_Impl::setParent(ParentObject& newParent)
{
  //if (newParent.optionalCast<SomeParentClass>() && (newParent.model() == model())) {
  //  return true;
  //}
  return false;
}

// return any children objects in the hierarchy
std::vector<ModelObject> LifeCycleCostRecurringCosts_Impl::children() const
{
  std::vector<ModelObject> result;
  return result;
}

std::vector<IddObjectType> LifeCycleCostRecurringCosts_Impl::allowableChildTypes() const {
  IddObjectTypeVector result;
  return result;
}

// Get all output variable names that could be associated with this object.
const std::vector<std::string>& LifeCycleCostRecurringCosts_Impl::outputVariableNames() const
{
  static std::vector<std::string> result;
  if (result.empty()){
  }
  return result;
}

} // detail

/// constructor
LifeCycleCostRecurringCosts::LifeCycleCostRecurringCosts(const Model& model)
  : ParentObject(LifeCycleCostRecurringCosts::iddObjectType(),model)
{
  BOOST_ASSERT(getImpl<detail::LifeCycleCostRecurringCosts_Impl>());
}

// constructor
LifeCycleCostRecurringCosts::LifeCycleCostRecurringCosts(boost::shared_ptr<detail::LifeCycleCostRecurringCosts_Impl> impl)
  : ParentObject(impl)
{}

OptionalInt LifeCycleCostRecurringCosts::yearsFromStart() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->yearsFromStart();
}

void LifeCycleCostRecurringCosts::setYearsFromStart(int num)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setYearsFromStart(num);
}

OptionalInt LifeCycleCostRecurringCosts::monthsFromStart() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->monthsFromStart();
}

void LifeCycleCostRecurringCosts::setMonthsFromStart(int num)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setMonthsFromStart(num);
}

OptionalInt LifeCycleCostRecurringCosts::repeatPeriodYears() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->repeatPeriodYears();
}

void LifeCycleCostRecurringCosts::setRepeatPeriodYears(int num)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setRepeatPeriodYears(num);
}

OptionalInt LifeCycleCostRecurringCosts::repeatPeriodMonths() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->repeatPeriodMonths();
}

void LifeCycleCostRecurringCosts::setRepeatPeriodMonths(int num)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setRepeatPeriodMonths(num);
}

OptionalDouble LifeCycleCostRecurringCosts::cost() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->cost();
}

void LifeCycleCostRecurringCosts::setCost(double num)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setCost(num);
}

OptionalDouble LifeCycleCostRecurringCosts::annualEscalationRate() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->annualEscalationRate();
}

void LifeCycleCostRecurringCosts::setAnnualEscalationRate(double num)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setAnnualEscalationRate(num);
}

OptionalString LifeCycleCostRecurringCosts::name() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->name();
}

void LifeCycleCostRecurringCosts::setName(const std::string& str)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setName(str);
}

OptionalString LifeCycleCostRecurringCosts::category() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->category();
}

void LifeCycleCostRecurringCosts::setCategory(const std::string& str)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setCategory(str);
}

OptionalString LifeCycleCostRecurringCosts::startOfCosts() const
{
  return getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->startOfCosts();
}

void LifeCycleCostRecurringCosts::setStartOfCosts(const std::string& str)
{
  getImpl<detail::LifeCycleCostRecurringCosts_Impl>()->setStartOfCosts(str);
}

IddObjectType LifeCycleCostRecurringCosts::iddObjectType()
{
  IddObjectType result(IddObjectType::OS_LifeCycleCost_RecurringCosts);
  return result;
}

} // model
} // openstudio

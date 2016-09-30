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

#ifndef MODEL_LIFECYCLECOSTRECURRINGCOSTS_IMPL_HPP
#define MODEL_LIFECYCLECOSTRECURRINGCOSTS_IMPL_HPP


#include <model/LifeCycleCostRecurringCosts.hpp>

#include <model/ParentObject_Impl.hpp>
#include <model/LifeCycleCostRecurringCosts.hpp>
#include <utilities/core/Optional.hpp>

namespace openstudio {
namespace model {
namespace detail {

class MODEL_API LifeCycleCostRecurringCosts_Impl : public ParentObject_Impl{

  Q_OBJECT;

public:
  // constructor
  LifeCycleCostRecurringCosts_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

  // construct from workspace
  LifeCycleCostRecurringCosts_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                 Model_Impl* model,
                 bool keepHandle);

  // clone copy constructor
  LifeCycleCostRecurringCosts_Impl(const LifeCycleCostRecurringCosts_Impl& other,Model_Impl* model,bool keepHandle);

  // virtual destructor
  virtual ~LifeCycleCostRecurringCosts_Impl(){}

  OptionalInt yearsFromStart() const;
  void setYearsFromStart(int num);

  OptionalInt monthsFromStart() const;
  void setMonthsFromStart(int num);

  OptionalInt repeatPeriodYears() const;
  void setRepeatPeriodYears(int num);

  OptionalInt repeatPeriodMonths() const;
  void setRepeatPeriodMonths(int num);

  boost::optional<double> cost() const;
  void setCost(double num);

  boost::optional<double> annualEscalationRate() const;
  void setAnnualEscalationRate(double num);

  OptionalString category() const;
  void setCategory(const std::string& str);

  OptionalString startOfCosts() const;
  void setStartOfCosts(const std::string& str);

  // return the parent object in the hierarchy
  virtual boost::optional<ParentObject> parent() const;

  // set the parent, child may have to call methods on the parent
  virtual bool setParent(ParentObject& newParent);

  // return any children objects in the hierarchy
  virtual std::vector<ModelObject> children() const;

  /// get a vector of allowable children types
  virtual std::vector<IddObjectType> allowableChildTypes() const;

  // Get all output variable names that could be associated with this object.
  virtual const std::vector<std::string>& outputVariableNames() const;

  virtual IddObjectType iddObjectType() const {return LifeCycleCostRecurringCosts::iddObjectType();}

private:
  REGISTER_LOGGER("openstudio.model.LifeCycleCostRecurringCosts");

};

} // detail
} // model
} // openstudio

#endif // MODEL_LIFECYCLECOSTRECURRINGCOSTS_IMPL_HPP

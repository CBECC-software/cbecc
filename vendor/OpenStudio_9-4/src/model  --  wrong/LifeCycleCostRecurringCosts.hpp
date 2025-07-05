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

#ifndef MODEL_LIFECYCLECOSTRECURRINGCOSTS_HPP
#define MODEL_LIFECYCLECOSTRECURRINGCOSTS_HPP

#include <model/ModelAPI.hpp>
#include <model/ParentObject.hpp>
#include <utilities/core/Optional.hpp>

namespace openstudio{
namespace model{

namespace detail{
  class LifeCycleCostRecurringCosts_Impl;
}

/** LifeCycleCostRecurringCosts derives from ParentObject and is an interface to the OpenStudio IDD object named "OS:LifeCycleCost:RecurringCost".
 *
 *  LifeCycleCostRecurringCosts is used to enter in a cost that occurs more than once during the analysis period.
 */
class MODEL_API LifeCycleCostRecurringCosts : public ParentObject{
 
public:

  /** @name Constructors and Destructors */
  //@{

  /// Constructs a new LifeCycleCost_NonrecurringCost object in the model.
  explicit LifeCycleCostRecurringCosts(const Model& model);

  virtual ~LifeCycleCostRecurringCosts() {}

  //@}
  /** @name Getters */
  //@{

  boost::optional<int> yearsFromStart() const;

  boost::optional<int> monthsFromStart() const;

  boost::optional<int> repeatPeriodYears() const;

  boost::optional<int> repeatPeriodMonths() const;

  boost::optional<double> cost() const;

  boost::optional<double> annualEscalationRate() const;

  boost::optional<std::string> name() const;

  boost::optional<std::string> category() const;

  boost::optional<std::string> startOfCosts() const;

  //@}
  /** @name Setters */
  //@{

  void setYearsFromStart(int yearsFromStart);

  void setMonthsFromStart(int monthsFromStart);

  void setRepeatPeriodYears(int repeatPeriodYears);

  void setRepeatPeriodMonths(int repeatPeriodMonths);

  void setCost(double cost);

  void setAnnualEscalationRate(double annualEscalationRate);

  void setName(const std::string& name);

  void setCategory(const std::string& category);

  void setStartOfCosts(const std::string& startOfCosts);

  //@}

  /// Returns the IddObjectType.
  static IddObjectType iddObjectType();

protected:

  /// @cond 

  typedef detail::LifeCycleCostRecurringCosts_Impl ImplType;

  friend class Model;
  friend class IdfObject;

  // constructor
  explicit LifeCycleCostRecurringCosts(boost::shared_ptr<detail::LifeCycleCostRecurringCosts_Impl> impl);

private:
  REGISTER_LOGGER("openstudio.model.LifeCycleCostRecurringCosts");

  /// @endcond

};

/** \relates LifeCycleCostRecurringCosts */
typedef boost::optional<LifeCycleCostRecurringCosts> OptionalLifeCycleCostRecurringCosts;

/** \relates LifeCycleCostRecurringCosts */
typedef std::vector<LifeCycleCostRecurringCosts> LifeCycleCostRecurringCostsVector;

} // model
} // openstudio

#endif // MODEL_LIFECYCLECOSTRECURRINGCOSTS_HPP

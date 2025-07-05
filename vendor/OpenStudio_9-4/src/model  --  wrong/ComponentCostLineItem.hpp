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

#ifndef MODEL_COMPONENTCOST_LINEITEM_HPP
#define MODEL_COMPONENTCOST_LINEITEM_HPP

#include <model/ModelAPI.hpp>
#include <model/ModelObject.hpp>
#include <model/ModelExtensibleGroup.hpp>

#include <utilities/core/Optional.hpp>

namespace openstudio{
namespace model{

namespace detail{
  class ComponentCostLineItem_Impl;
}

/** ComponentRecurringCost is a ModelExtensibleGroup that represents a single recurring cost 
 *  contained in a ComponentCostLineItem ModelObject. */
class MODEL_API ComponentRecurringCost : public ModelExtensibleGroup {
 public:
  /** @name Getters */
  //@{

  std::string name() const;

  std::string costType() const;

  double cost() const;

  std::string costUnits() const; 

  int costIntervalYears() const;
  bool isCostIntervalYearsDefaulted() const;

  int costIntervalMonths() const;
  bool isCostIntervalMonthsDefaulted() const;

  //@}
  /** @name Setters */
  //@{

  bool setName(const std::string& name);

  bool setCostType(const std::string& costType);

  bool setCost(double cost);

  bool setCostUnits(const std::string& costUnits);

  bool setCostIntervalYears(int costIntervalYears);
  void resetCostIntervalYears();

  bool setCostIntervalMonths(int costIntervalMonths);
  void resetCostIntervalMonths();

  //@}
 protected:
  /// @cond
  typedef detail::ComponentCostLineItem_Impl ImplType;

  friend class IdfExtensibleGroup;
  friend class detail::ComponentCostLineItem_Impl;

  ComponentRecurringCost(boost::shared_ptr<detail::ComponentCostLineItem_Impl> impl,unsigned index);

  /// @endcond
 private:

  /** Private default constructor. */
  ComponentRecurringCost();

  REGISTER_LOGGER("openstudio.model.ComponentRecurringCost");
};

/** \relates ComponentRecurringCost */
typedef std::vector<ComponentRecurringCost> ComponentRecurringCostVector;


/** ComponentCostLineItem derives from ModelObject and is an interface to the OpenStudio IDD object named "OS:ComponentCost:LineItem".
 *
 *  ComponentCostLineItem objects are used to add costs related to building construction and operation.  Each ModelObject can
 *  have ComponentCostLineItems.  The ComponentCostLineItem's lineItemType will be set based on the type of ModelObject.
 */
class MODEL_API ComponentCostLineItem : public ModelObject {

public:
    
  /** @name Constructors and Destructors */
  //@{

  /// Constructs a new ComponentCostLineItem object in the model.
  /// This will throw if the object type is not known
  explicit ComponentCostLineItem(const ModelObject& modelObject);

  virtual ~ComponentCostLineItem() {}

  //@}
  /** @name Static Methods */
  //@{

  static IddObjectType iddObjectType();

  static std::vector<std::string> validLineItemTypeValues();

  //@}
  /** @name Getters */
  //@{

  std::vector<std::string> validMaterialCostUnitsValues() const;

  std::vector<std::string> validInstallationCostUnitsValues() const;

  std::vector<std::string> validDemolitionCostUnitsValues() const;

  std::vector<std::string> validSalvageValueUnitsValues() const;

  std::vector<std::string> validRecurringCostUnitsValues() const;

  std::string lineItemType() const;

  ModelObject item() const;

  boost::optional<double> materialCost() const;

  boost::optional<std::string> materialCostUnits() const;

  boost::optional<double> installationCost() const;

  boost::optional<std::string> installationCostUnits() const;

  boost::optional<int> expectedLife() const;

  boost::optional<double> demolitionCost() const;

  boost::optional<std::string> demolitionCostUnits() const;

  boost::optional<double> salvageValue() const;

  boost::optional<std::string> salvageValueUnits() const;

  std::vector<ComponentRecurringCost> componentRecurringCosts() const;

  //@}
  /** @name Setters */
  //@{

  bool setMaterialCost(double materialCost);

  void resetMaterialCost();

  bool setMaterialCostUnits(const std::string& materialCostUnits);

  void resetMaterialCostUnits();

  bool setInstallationCost(double installationCost);

  void resetInstallationCost();

  bool setInstallationCostUnits(const std::string& installationCostUnits);

  void resetInstallationCostUnits();

  bool setExpectedLife(int expectedLife);

  void resetExpectedLife();

  bool setDemolitionCost(double demolitionCost);

  void resetDemolitionCost();

  bool setDemolitionCostUnits(const std::string& demolitionCostUnits);

  void resetDemolitionCostUnits();

  bool setSalvageValue(double salvageValue);

  void resetSalvageValue();

  bool setSalvageValueUnits(const std::string& salvageValueUnits);

  void resetSalvageValueUnits();

  void clearComponentRecurringCosts();

  boost::optional<ComponentRecurringCost> addComponentRecurringCost(const std::string& name,
    const std::string& costType, double cost, const std::string& costUnits);

  //@}

  /// copy costs from other line item to this one
  void copyCosts(const ComponentCostLineItem& otherLineItem);

  /// compute the area that would be used for CostPerArea
  boost::optional<double> costedArea() const;

  /// convert all CostPerArea type costs to CostPerEach
  /// optional second argument is used to hard size only non-capital costs
  void hardSizeCostPerArea(bool hardSizeOnlyNonCapitalCosts=false);
  void hardSizeCostPerArea(double area, bool hardSizeOnlyNonCapitalCosts=false);

protected:

  /// @cond
  typedef detail::ComponentCostLineItem_Impl ImplType;

  friend class Model;
  friend class IdfObject;

  // constructor
  explicit ComponentCostLineItem(boost::shared_ptr<detail::ComponentCostLineItem_Impl> impl);

private:
  REGISTER_LOGGER("openstudio.model.ComponentCostLineItem");

  /// @endcond

};

/** \relates ComponentCostLineItem */
typedef boost::optional<ComponentCostLineItem> OptionalComponentCostLineItem;

/** \relates ComponentCostLineItem */
typedef std::vector<ComponentCostLineItem> ComponentCostLineItemVector;

} // model
} // openstudio

#endif // MODEL_COMPONENTCOST_LINEITEM_HPP

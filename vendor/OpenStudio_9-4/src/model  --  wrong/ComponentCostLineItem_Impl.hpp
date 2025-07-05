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

#ifndef MODEL_COMPONENTCOSTLINEITEM_IMPL_HPP
#define MODEL_COMPONENTCOSTLINEITEM_IMPL_HPP

#include <model/ParentObject_Impl.hpp>
#include <model/ComponentCostLineItem.hpp>

#include <utilities/core/Optional.hpp>

namespace openstudio {
namespace model {
  
  class SpaceLoadInstance;
  class SpaceLoadDefinition;

namespace detail {

class MODEL_API ComponentCostLineItem_Impl : public ModelObject_Impl
{
  Q_OBJECT;
  Q_PROPERTY(const std::string& lineItemType READ lineItemType);
  Q_PROPERTY(boost::optional<double> materialCost READ materialCost WRITE setMaterialCost RESET resetMaterialCost);
  Q_PROPERTY(const boost::optional<std::string>& materialCostUnits READ materialCostUnits WRITE setMaterialCostUnits RESET resetMaterialCostUnits);
  Q_PROPERTY(boost::optional<double> installationCost READ installationCost WRITE setInstallationCost RESET resetInstallationCost);
  Q_PROPERTY(const boost::optional<std::string>& installationCostUnits READ installationCostUnits WRITE setInstallationCostUnits RESET resetInstallationCostUnits);
  Q_PROPERTY(boost::optional<int> expectedLife READ expectedLife WRITE setExpectedLife RESET resetExpectedLife);
  Q_PROPERTY(boost::optional<double> demolitionCost READ demolitionCost WRITE setDemolitionCost RESET resetDemolitionCost);
  Q_PROPERTY(const boost::optional<std::string>& demolitionCostUnits READ demolitionCostUnits WRITE setDemolitionCostUnits RESET resetDemolitionCostUnits);
  Q_PROPERTY(boost::optional<double> salvageValue READ salvageValue WRITE setSalvageValue RESET resetSalvageValue);
  Q_PROPERTY(const boost::optional<std::string>& salvageValueUnits READ salvageValueUnits WRITE setSalvageValueUnits RESET resetSalvageValueUnits);
public:
  // constructor
  ComponentCostLineItem_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

  // construct from workspace
  ComponentCostLineItem_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                 Model_Impl* model,
                 bool keepHandle);

  // clone copy constructor
  ComponentCostLineItem_Impl(const ComponentCostLineItem_Impl& other,Model_Impl* model,bool keepHandle);

  // virtual destructor
  virtual ~ComponentCostLineItem_Impl(){}

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

  bool setMaterialCost(boost::optional<double> materialCost);

  bool setMaterialCost(double materialCost);

  void resetMaterialCost();

  bool setMaterialCostUnits(const boost::optional<std::string>& materialCostUnits);

  bool setMaterialCostUnits(const std::string& materialCostUnits);

  void resetMaterialCostUnits();

  bool setInstallationCost(boost::optional<double> installationCost);

  bool setInstallationCost(double installationCost);

  void resetInstallationCost();

  bool setInstallationCostUnits(const boost::optional<std::string>& installationCostUnits);

  bool setInstallationCostUnits(const std::string& installationCostUnits);

  void resetInstallationCostUnits();

  bool setExpectedLife(boost::optional<int> expectedLife);

  bool setExpectedLife(int expectedLife);

  void resetExpectedLife();

  bool setDemolitionCost(boost::optional<double> demolitionCost);

  bool setDemolitionCost(double demolitionCost);

  void resetDemolitionCost();

  bool setDemolitionCostUnits(const boost::optional<std::string>& demolitionCostUnits);

  bool setDemolitionCostUnits(const std::string& demolitionCostUnits);

  void resetDemolitionCostUnits();

  bool setSalvageValue(boost::optional<double> salvageValue);

  bool setSalvageValue(double salvageValue);

  void resetSalvageValue();

  bool setSalvageValueUnits(const boost::optional<std::string>& salvageValueUnits);

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
  void hardSizeCostPerArea(bool hardSizeOnlyNonCapitalCosts);
  void hardSizeCostPerArea(double area, bool hardSizeOnlyNonCapitalCosts);

  // Get all output variable names that could be associated with this object.
  virtual const std::vector<std::string>& outputVariableNames() const;

  virtual IddObjectType iddObjectType() const {return ComponentCostLineItem::iddObjectType();}

private:
  REGISTER_LOGGER("openstudio.model.ComponentCost_LineItem");

  double getArea(const SpaceLoadInstance& spaceLoadInstance) const;
  double getArea(const SpaceLoadDefinition& spaceLoadDefinition) const;
};

} // detail
} // model
} // openstudio

#endif // MODEL_COMPONENTCOSTLINEITEM_IMPL_HPP

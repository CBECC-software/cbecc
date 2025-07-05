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

#include <model/ComponentCostLineItem.hpp>
#include <model/ComponentCostLineItem_Impl.hpp>
#include <model/CoilCoolingDXSingleSpeed.hpp>
#include <model/CoilCoolingDXSingleSpeed_Impl.hpp>
#include <model/CoilHeatingGas.hpp>
#include <model/CoilHeatingGas_Impl.hpp>
#include <model/ConstructionBase.hpp>
#include <model/ConstructionBase_Impl.hpp>
#include <model/DaylightingControl.hpp>
#include <model/DaylightingControl_Impl.hpp>
#include <model/GlareSensor.hpp>
#include <model/GlareSensor_Impl.hpp>
#include <model/Lights.hpp>
#include <model/Lights_Impl.hpp>
#include <model/LightsDefinition.hpp>
#include <model/LightsDefinition_Impl.hpp>
#include <model/ElectricEquipment.hpp>
#include <model/ElectricEquipment_Impl.hpp>
#include <model/ElectricEquipmentDefinition.hpp>
#include <model/ElectricEquipmentDefinition_Impl.hpp>
#include <model/GasEquipment.hpp>
#include <model/GasEquipment_Impl.hpp>
#include <model/GasEquipmentDefinition.hpp>
#include <model/GasEquipmentDefinition_Impl.hpp>
#include <model/HotWaterEquipment.hpp>
#include <model/HotWaterEquipment_Impl.hpp>
#include <model/HotWaterEquipmentDefinition.hpp>
#include <model/HotWaterEquipmentDefinition_Impl.hpp>
#include <model/SteamEquipment.hpp>
#include <model/SteamEquipment_Impl.hpp>
#include <model/SteamEquipmentDefinition.hpp>
#include <model/SteamEquipmentDefinition_Impl.hpp>
#include <model/Building.hpp>
#include <model/Building_Impl.hpp>
#include <model/Space.hpp>
#include <model/ThermalZone.hpp>
#include <model/Model.hpp>
#include <model/Model_Impl.hpp>

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/OS_ComponentCost_LineItem_FieldEnums.hxx>

#include <utilities/core/Assert.hpp>

#include <boost/algorithm/string.hpp>

#include <typeinfo>
#include <iostream>
using namespace std;

using std::string;
using std::type_info;

namespace openstudio {
namespace model  {
namespace detail {

ComponentCostLineItem_Impl::ComponentCostLineItem_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
  : ModelObject_Impl(idfObject, model, keepHandle)
{
  BOOST_ASSERT(idfObject.iddObject().type() == ComponentCostLineItem::iddObjectType());
}

ComponentCostLineItem_Impl::ComponentCostLineItem_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                           Model_Impl* model,
                                           bool keepHandle)
  : ModelObject_Impl(other,model,keepHandle)
{
  BOOST_ASSERT(other.iddObject().type() == ComponentCostLineItem::iddObjectType());
}

ComponentCostLineItem_Impl::ComponentCostLineItem_Impl(const ComponentCostLineItem_Impl& other,Model_Impl* model,bool keepHandle)
  : ModelObject_Impl(other,model,keepHandle)
{
}

std::vector<std::string> ComponentCostLineItem_Impl::validMaterialCostUnitsValues() const
{
  std::vector<std::string> result;
  std::string lineItemType = this->lineItemType();
  if (istringEqual("Construction", lineItemType)){
    result.push_back("CostPerArea");
  }else if (istringEqual("Lights", lineItemType)){
    result.push_back("CostPerEach");
    result.push_back("CostPerArea");
  }else if (istringEqual("Equipment", lineItemType)){
    result.push_back("CostPerEach");
    result.push_back("CostPerArea");
  }else if (istringEqual("Building", lineItemType)){
    result.push_back("CostPerEach");
    result.push_back("CostPerArea");
  }else if (istringEqual("Daylighting:Controls", lineItemType)){
    result.push_back("CostPerEach");
    result.push_back("CostPerArea");
  }else{
    result.push_back("CostPerEach");
  }
  
  return result;
}

std::vector<std::string> ComponentCostLineItem_Impl::validInstallationCostUnitsValues() const
{
  return validMaterialCostUnitsValues();
}

std::vector<std::string> ComponentCostLineItem_Impl::validDemolitionCostUnitsValues() const
{
  return validMaterialCostUnitsValues();
}

std::vector<std::string> ComponentCostLineItem_Impl::validSalvageValueUnitsValues() const
{
  return validMaterialCostUnitsValues();
}

std::vector<std::string> ComponentCostLineItem_Impl::validRecurringCostUnitsValues() const
{
  return validMaterialCostUnitsValues();
}

std::string ComponentCostLineItem_Impl::lineItemType() const {
  boost::optional<std::string> value = getString(OS_ComponentCost_LineItemFields::LineItemType,true);
  BOOST_ASSERT(value);
  return value.get();
}

ModelObject ComponentCostLineItem_Impl::item() const {
  boost::optional<ModelObject> value = getObject<ModelObject>().getModelObjectTarget<ModelObject>(OS_ComponentCost_LineItemFields::ItemName);
  BOOST_ASSERT(value);
  return value.get();
}

boost::optional<double> ComponentCostLineItem_Impl::materialCost() const {
  return getDouble(OS_ComponentCost_LineItemFields::MaterialCost,true);
}

boost::optional<std::string> ComponentCostLineItem_Impl::materialCostUnits() const {
  return getString(OS_ComponentCost_LineItemFields::MaterialCostUnits,true);
}

boost::optional<double> ComponentCostLineItem_Impl::installationCost() const {
  return getDouble(OS_ComponentCost_LineItemFields::InstallationCost,true);
}

boost::optional<std::string> ComponentCostLineItem_Impl::installationCostUnits() const {
  return getString(OS_ComponentCost_LineItemFields::InstallationCostUnits,true);
}

boost::optional<int> ComponentCostLineItem_Impl::expectedLife() const {
  return getInt(OS_ComponentCost_LineItemFields::ExpectedLife,true);
}

boost::optional<double> ComponentCostLineItem_Impl::demolitionCost() const {
  return getDouble(OS_ComponentCost_LineItemFields::DemolitionCost,true);
}

boost::optional<std::string> ComponentCostLineItem_Impl::demolitionCostUnits() const {
  return getString(OS_ComponentCost_LineItemFields::DemolitionCostUnits,true);
}

boost::optional<double> ComponentCostLineItem_Impl::salvageValue() const {
  return getDouble(OS_ComponentCost_LineItemFields::SalvageValue,true);
}

boost::optional<std::string> ComponentCostLineItem_Impl::salvageValueUnits() const {
  return getString(OS_ComponentCost_LineItemFields::SalvageValueUnits,true);
}

std::vector<ComponentRecurringCost> ComponentCostLineItem_Impl::componentRecurringCosts() const
{
  IdfExtensibleGroupVector egs = extensibleGroups();
  ComponentRecurringCostVector result;
  BOOST_FOREACH(const IdfExtensibleGroup& eg,egs) {
    result.push_back(eg.cast<ComponentRecurringCost>());
  }
  return result;
}

bool ComponentCostLineItem_Impl::setMaterialCost(boost::optional<double> materialCost) {
  bool result = true;
  if (materialCost) {
    result = setMaterialCost(*materialCost);
  } else {
    resetMaterialCost();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setMaterialCost(double materialCost) {
  bool result = setDouble(OS_ComponentCost_LineItemFields::MaterialCost, materialCost);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::MaterialCostUnits)){
    result = setString(OS_ComponentCost_LineItemFields::MaterialCostUnits, validMaterialCostUnitsValues()[0]);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetMaterialCost() {
  bool result = setString(OS_ComponentCost_LineItemFields::MaterialCost, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::MaterialCostUnits, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setMaterialCostUnits(const boost::optional<std::string>& materialCostUnits) {
  bool result = true;
  if (materialCostUnits) {
    result = setMaterialCostUnits(*materialCostUnits);
  } else {
    resetMaterialCostUnits();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setMaterialCostUnits(const std::string& materialCostUnits) {
  std::vector<std::string> validMaterialCostUnitsValues = this->validMaterialCostUnitsValues();
  if (std::find(validMaterialCostUnitsValues.begin(), validMaterialCostUnitsValues.end(), materialCostUnits) == validMaterialCostUnitsValues.end()){
    return false;
  }

  bool result = setString(OS_ComponentCost_LineItemFields::MaterialCostUnits, materialCostUnits);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::MaterialCost)){
    result = setDouble(OS_ComponentCost_LineItemFields::MaterialCost, 0.0);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetMaterialCostUnits() {
  bool result = setString(OS_ComponentCost_LineItemFields::MaterialCost, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::MaterialCostUnits, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setInstallationCost(boost::optional<double> installationCost) {
  bool result = true;
  if (installationCost) {
    result = setInstallationCost(*installationCost);
  } else {
    resetInstallationCost();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setInstallationCost(double installationCost) {
  bool result = setDouble(OS_ComponentCost_LineItemFields::InstallationCost, installationCost);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::InstallationCostUnits)){
    result = setString(OS_ComponentCost_LineItemFields::InstallationCostUnits, validInstallationCostUnitsValues()[0]);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetInstallationCost() {
  bool result = setString(OS_ComponentCost_LineItemFields::InstallationCost, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::InstallationCostUnits, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setInstallationCostUnits(const boost::optional<std::string>& installationCostUnits) {
  bool result = true;
  if (installationCostUnits) {
    result = setInstallationCostUnits(*installationCostUnits);
  } else {
    resetInstallationCostUnits();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setInstallationCostUnits(const std::string& installationCostUnits) {
  std::vector<std::string> validInstallationCostUnitsValues = this->validInstallationCostUnitsValues();
  if (std::find(validInstallationCostUnitsValues.begin(), validInstallationCostUnitsValues.end(), installationCostUnits) == validInstallationCostUnitsValues.end()){
    return false;
  }

  bool result = setString(OS_ComponentCost_LineItemFields::InstallationCostUnits, installationCostUnits);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::InstallationCost)){
    result = setDouble(OS_ComponentCost_LineItemFields::InstallationCost, 0.0);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetInstallationCostUnits() {
  bool result = setString(OS_ComponentCost_LineItemFields::InstallationCost, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::InstallationCostUnits, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setExpectedLife(boost::optional<int> expectedLife) {
  bool result = false;
  if (expectedLife) {
    result = setInt(OS_ComponentCost_LineItemFields::ExpectedLife, expectedLife.get());
  } else {
    result = setString(OS_ComponentCost_LineItemFields::ExpectedLife, "");
  }
  return result;
}

bool ComponentCostLineItem_Impl::setExpectedLife(int expectedLife) {
  bool result = false;
  result = setInt(OS_ComponentCost_LineItemFields::ExpectedLife, expectedLife);
  return result;
}

void ComponentCostLineItem_Impl::resetExpectedLife() {
  bool result = setString(OS_ComponentCost_LineItemFields::ExpectedLife, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setDemolitionCost(boost::optional<double> demolitionCost) {
  bool result = true;
  if (demolitionCost) {
    result = setDemolitionCost(*demolitionCost);
  } else {
    resetDemolitionCost();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setDemolitionCost(double demolitionCost) {
  bool result = setDouble(OS_ComponentCost_LineItemFields::DemolitionCost, demolitionCost);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::DemolitionCostUnits)){
    result = setString(OS_ComponentCost_LineItemFields::DemolitionCostUnits, validDemolitionCostUnitsValues()[0]);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetDemolitionCost() {
  bool result = setString(OS_ComponentCost_LineItemFields::DemolitionCost, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::DemolitionCostUnits, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setDemolitionCostUnits(const boost::optional<std::string>& demolitionCostUnits) {
  bool result = true;
  if (demolitionCostUnits) {
    result = setDemolitionCostUnits(*demolitionCostUnits);
  } else {
    resetDemolitionCostUnits();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setDemolitionCostUnits(const std::string& demolitionCostUnits) {
  std::vector<std::string> validDemolitionCostUnitsValues = this->validDemolitionCostUnitsValues();
  if (std::find(validDemolitionCostUnitsValues.begin(), validDemolitionCostUnitsValues.end(), demolitionCostUnits) == validDemolitionCostUnitsValues.end()){
    return false;
  }

  bool result = setString(OS_ComponentCost_LineItemFields::DemolitionCostUnits, demolitionCostUnits);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::DemolitionCost)){
    result = setDouble(OS_ComponentCost_LineItemFields::DemolitionCost, 0.0);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetDemolitionCostUnits() {
  bool result = setString(OS_ComponentCost_LineItemFields::DemolitionCost, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::DemolitionCostUnits, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setSalvageValue(boost::optional<double> salvageValue) {
  bool result = true;
  if (salvageValue) {
    result = setSalvageValue(*salvageValue);
  } else {
    resetSalvageValue();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setSalvageValue(double salvageValue) {
  bool result = setDouble(OS_ComponentCost_LineItemFields::SalvageValue, salvageValue);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::SalvageValueUnits)){
    result = setString(OS_ComponentCost_LineItemFields::SalvageValueUnits, validSalvageValueUnitsValues()[0]);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetSalvageValue() {
  bool result = setString(OS_ComponentCost_LineItemFields::SalvageValue, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::SalvageValueUnits, "");
  BOOST_ASSERT(result);
}

bool ComponentCostLineItem_Impl::setSalvageValueUnits(const boost::optional<std::string>& salvageValueUnits) {
  bool result = true;
  if (salvageValueUnits) {
    result = setSalvageValueUnits(*salvageValueUnits);
  } else {
    resetSalvageValueUnits();
  }
  return result;
}

bool ComponentCostLineItem_Impl::setSalvageValueUnits(const std::string& salvageValueUnits) {
  std::vector<std::string> validSalvageValueUnitsValues = this->validSalvageValueUnitsValues();
  if (std::find(validSalvageValueUnitsValues.begin(), validSalvageValueUnitsValues.end(), salvageValueUnits) == validSalvageValueUnitsValues.end()){
    return false;
  }

  bool result = setString(OS_ComponentCost_LineItemFields::SalvageValueUnits, salvageValueUnits);
  if (result && isEmpty(OS_ComponentCost_LineItemFields::SalvageValue)){
    result = setDouble(OS_ComponentCost_LineItemFields::SalvageValue, 0.0);
  }
  return result;
}

void ComponentCostLineItem_Impl::resetSalvageValueUnits() {
  bool result = setString(OS_ComponentCost_LineItemFields::SalvageValue, "");
  BOOST_ASSERT(result);
  result = setString(OS_ComponentCost_LineItemFields::SalvageValueUnits, "");
  BOOST_ASSERT(result);
}

void ComponentCostLineItem_Impl::clearComponentRecurringCosts()
{
  clearExtensibleGroups();
}

boost::optional<ComponentRecurringCost> ComponentCostLineItem_Impl::addComponentRecurringCost(const std::string& name,
  const std::string& costType, double cost, const std::string& costUnits)
{
  StringVector values;
  values.push_back(name);
  values.push_back(costType);
  std::stringstream ss;
  ss << cost;
  values.push_back(ss.str());
  values.push_back(costUnits);
  values.push_back("");
  values.push_back("");

  IdfExtensibleGroup eg = pushExtensibleGroup(values);
  if (eg.empty()) {
    return boost::none;
  }
  return eg.cast<ComponentRecurringCost>();
}

void ComponentCostLineItem_Impl::copyCosts(const ComponentCostLineItem& otherLineItem)
{
  if (otherLineItem.handle() == this->handle()){
    return;
  }

  // check that line item type's are compatible?

  boost::optional<double> d;

  d = otherLineItem.materialCost();
  if (d){
    this->setMaterialCost(*d);
  }else{
    this->resetMaterialCost();
  }

  boost::optional<std::string> s = otherLineItem.materialCostUnits();
  if (s){
    this->setMaterialCostUnits(*s);
  }else{
    this->resetMaterialCostUnits();
  }

  d = otherLineItem.installationCost();
  if (d){
    this->setInstallationCost(*d);
  }else{
    this->resetInstallationCost();
  }

  s = otherLineItem.installationCostUnits();
  if (s){
    this->setInstallationCostUnits(*s);
  }else{
    this->resetInstallationCostUnits();
  }

  d = otherLineItem.expectedLife();
  if (d){
    this->setExpectedLife(*d);
  }else{
    this->resetExpectedLife();
  }

  d = otherLineItem.demolitionCost();
  if (d){
    this->setDemolitionCost(*d);
  }else{
    this->resetDemolitionCost();
  }

  s = otherLineItem.demolitionCostUnits();
  if (s){
    this->setDemolitionCostUnits(*s);
  }else{
    this->resetDemolitionCostUnits();
  }

  d = otherLineItem.salvageValue();
  if (d){
    this->setSalvageValue(*d);
  }else{
    this->resetSalvageValue();
  }

  s = otherLineItem.salvageValueUnits();
  if (s){
    this->setSalvageValueUnits(*s);
  }else{
    this->resetSalvageValueUnits();
  }

  this->clearComponentRecurringCosts();
  BOOST_FOREACH(const ComponentRecurringCost& otherRecurringCost, otherLineItem.componentRecurringCosts()){
    boost::optional<ComponentRecurringCost> recurringCost = addComponentRecurringCost(otherRecurringCost.name(), otherRecurringCost.costType(), otherRecurringCost.cost(), otherRecurringCost.costUnits());
    if (recurringCost){
      if (!otherRecurringCost.isCostIntervalYearsDefaulted()){
        recurringCost->setCostIntervalYears(otherRecurringCost.costIntervalYears());
      }
      if (!otherRecurringCost.isCostIntervalMonthsDefaulted()){
        recurringCost->setCostIntervalMonths(otherRecurringCost.costIntervalMonths());
      }
    }
  }

}

boost::optional<double> ComponentCostLineItem_Impl::costedArea() const
{
  boost::optional<double> result;

  ModelObject modelObject = item();

  if (modelObject.optionalCast<ConstructionBase>()){
    result = modelObject.cast<ConstructionBase>().getNetArea(); 
  }else if (modelObject.optionalCast<Lights>()){
    result = getArea(modelObject.cast<Lights>());
  }else if (modelObject.optionalCast<LightsDefinition>()){
    result = getArea(modelObject.cast<LightsDefinition>());
  }else if (modelObject.optionalCast<ElectricEquipment>()){
    result = getArea(modelObject.cast<ElectricEquipment>());
  }else if (modelObject.optionalCast<ElectricEquipmentDefinition>()){
    result = getArea(modelObject.cast<ElectricEquipmentDefinition>());
  }else if (modelObject.optionalCast<GasEquipment>()){
    result = getArea(modelObject.cast<GasEquipment>());
  }else if (modelObject.optionalCast<GasEquipmentDefinition>()){
    result = getArea(modelObject.cast<GasEquipmentDefinition>());
  }else if (modelObject.optionalCast<HotWaterEquipment>()){
    result = getArea(modelObject.cast<HotWaterEquipment>());
  }else if (modelObject.optionalCast<HotWaterEquipmentDefinition>()){
    result = getArea(modelObject.cast<HotWaterEquipmentDefinition>());
  }else if (modelObject.optionalCast<SteamEquipment>()){
    result = getArea(modelObject.cast<SteamEquipment>());
  }else if (modelObject.optionalCast<SteamEquipmentDefinition>()){
    result = getArea(modelObject.cast<SteamEquipmentDefinition>());
  }else if (modelObject.optionalCast<Building>()){
    // DLM: this should possibly be conditioned floor area but that requires sql file
    result = modelObject.cast<Building>().floorArea();
  }else if (modelObject.optionalCast<DaylightingControl>()){
    boost::optional<Space> space = modelObject.cast<DaylightingControl>().space();
    if (space){
      boost::optional<ThermalZone> thermalZone = space->thermalZone();
      if (thermalZone){
        if (modelObject.cast<DaylightingControl>().isPrimaryDaylightingControl()){
          result = space->multiplier() * space->floorArea() * thermalZone->fractionofZoneControlledbyPrimaryDaylightingControl();
        }else if (modelObject.cast<DaylightingControl>().isSecondaryDaylightingControl()){
          result = space->multiplier() * space->floorArea() * thermalZone->fractionofZoneControlledbySecondaryDaylightingControl();
        }
      }
    }
  }

  return result;
}

void ComponentCostLineItem_Impl::hardSizeCostPerArea(bool hardSizeOnlyNonCapitalCosts)
{
  boost::optional<double> costedArea = this->costedArea();
  if (costedArea){
    hardSizeCostPerArea(*costedArea, hardSizeOnlyNonCapitalCosts);
  }
}

void ComponentCostLineItem_Impl::hardSizeCostPerArea(double area, bool hardSizeOnlyNonCapitalCosts)
{
  if (!hardSizeOnlyNonCapitalCosts){
    // DLM: this will not work for constructions

    OptionalDouble materialCost = this->materialCost();
    OptionalString materialCostUnits = this->materialCostUnits();
    if (materialCost && materialCostUnits && istringEqual("CostPerArea", *materialCostUnits)){
      this->setMaterialCost(area*materialCost.get());
      this->setMaterialCostUnits("CostPerEach");
    }
    OptionalDouble installationCost = this->installationCost();
    OptionalString installationCostUnits = this->installationCostUnits();
    if (installationCost && installationCostUnits && istringEqual("CostPerArea", *installationCostUnits)){
      this->setInstallationCost(area*installationCost.get());
      this->setInstallationCostUnits("CostPerEach");
    }
  }
  OptionalDouble demolitionCost = this->demolitionCost();
  OptionalString demolitionCostUnits = this->demolitionCostUnits();
  if (demolitionCost && demolitionCostUnits && istringEqual("CostPerArea", *demolitionCostUnits)){
    this->setDemolitionCost(area*demolitionCost.get());
    this->setDemolitionCostUnits("CostPerEach");
  }
  OptionalDouble salvageValue = this->salvageValue();
  OptionalString salvageValueUnits = this->salvageValueUnits();
  if (salvageValue && salvageValueUnits && istringEqual("CostPerArea", *demolitionCostUnits)){
    this->setSalvageValue(area*salvageValue.get());
    this->setSalvageValueUnits("CostPerEach");
  }
  BOOST_FOREACH(ComponentRecurringCost recurringCost, this->componentRecurringCosts()){
    if (istringEqual("CostPerArea", recurringCost.costUnits())){
      recurringCost.setCost(area*recurringCost.cost());
      recurringCost.setCostUnits("CostPerEach");
    }
  }
}


// Get all output variable names that could be associated with this object.
const std::vector<std::string>& ComponentCostLineItem_Impl::outputVariableNames() const
{
  static std::vector<std::string> result;
  if (result.empty()){
  }
  return result;
}

double ComponentCostLineItem_Impl::getArea(const SpaceLoadInstance& spaceLoadInstance) const
{
  double area = 0;
  boost::optional<Space> space = spaceLoadInstance.space();
  if (space){
    area = space->multiplier() * space->floorArea();
  }

  double multiplier = 1.0;
  if (spaceLoadInstance.optionalCast<Lights>()){
    multiplier = spaceLoadInstance.cast<Lights>().multiplier();
  }else if (spaceLoadInstance.optionalCast<ElectricEquipment>()){
    multiplier = spaceLoadInstance.cast<ElectricEquipment>().multiplier();
  }else if (spaceLoadInstance.optionalCast<GasEquipment>()){
    multiplier = spaceLoadInstance.cast<GasEquipment>().multiplier();
  }else if (spaceLoadInstance.optionalCast<HotWaterEquipment>()){
    multiplier = spaceLoadInstance.cast<HotWaterEquipment>().multiplier();
  }else if (spaceLoadInstance.optionalCast<SteamEquipment>()){
    multiplier = spaceLoadInstance.cast<SteamEquipment>().multiplier();
  }

  return multiplier*area;
}

double ComponentCostLineItem_Impl::getArea(const SpaceLoadDefinition& spaceLoadDefinition) const
{
  double area = 0;
  BOOST_FOREACH(const SpaceLoadInstance& spaceLoadInstance, spaceLoadDefinition.instances()){
    area += getArea(spaceLoadInstance);
  }
  return area;
}

} // detail


// ComponentRecurringCost

std::string ComponentRecurringCost::name() const {
  BOOST_ASSERT(!empty());
  std::string result;
  OptionalString os = getString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostName,true);
  if (os) { result = *os; }
  return result;
}

std::string ComponentRecurringCost::costType() const {
  BOOST_ASSERT(!empty());
  std::string result;
  OptionalString os = getString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostType,true);
  if (os) { result = *os; }
  return result;
}

double ComponentRecurringCost::cost() const {
  BOOST_ASSERT(!empty());
  boost::optional<double> result = getDouble(OS_ComponentCost_LineItemExtensibleFields::RecurringCost,true);
  return *result;
}

std::string ComponentRecurringCost::costUnits() const {
  BOOST_ASSERT(!empty());
  std::string result;
  OptionalString os = getString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostUnits,true);
  if (os) { result = *os; }
  return result;
}

int ComponentRecurringCost::costIntervalYears() const {
  BOOST_ASSERT(!empty());
  boost::optional<int> result = getInt(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalYears,true);
  BOOST_ASSERT(result);
  return *result;
}

bool ComponentRecurringCost::isCostIntervalYearsDefaulted() const {
  BOOST_ASSERT(!empty());
  return isEmpty(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalYears);
}

int ComponentRecurringCost::costIntervalMonths() const {
  BOOST_ASSERT(!empty());
  boost::optional<int> result = getInt(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalMonths,true);
  BOOST_ASSERT(result);
  return *result;
}

bool ComponentRecurringCost::isCostIntervalMonthsDefaulted() const {
  BOOST_ASSERT(!empty());
  return isEmpty(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalMonths);
}

bool ComponentRecurringCost::setName(const std::string& name) {
  return setString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostName,name);
}

bool ComponentRecurringCost::setCostType(const std::string& costType) {
  return setString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostType,costType);
}

bool ComponentRecurringCost::setCost(double cost) {
  bool result = setDouble(OS_ComponentCost_LineItemExtensibleFields::RecurringCost,cost);
  if (result && isEmpty(OS_ComponentCost_LineItemExtensibleFields::RecurringCostUnits)){
    result = setString(OS_ComponentCost_LineItemExtensibleFields::RecurringCost, getImpl<detail::ComponentCostLineItem_Impl>()->validRecurringCostUnitsValues()[0]);
  }
  return result;
}

bool ComponentRecurringCost::setCostUnits(const std::string& costUnits) {
  std::vector<std::string> validRecurringCostUnitsValues = getImpl<detail::ComponentCostLineItem_Impl>()->validRecurringCostUnitsValues();
  if (std::find(validRecurringCostUnitsValues.begin(), validRecurringCostUnitsValues.end(), costUnits) == validRecurringCostUnitsValues.end()){
    return false;
  }

  bool result = setString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostUnits,costUnits);
  if (result && isEmpty(OS_ComponentCost_LineItemExtensibleFields::RecurringCost)){
    result = setDouble(OS_ComponentCost_LineItemExtensibleFields::RecurringCost,0.0);
  }
  return result;
}

bool ComponentRecurringCost::setCostIntervalYears(int costIntervalYears) {
  return setInt(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalYears,costIntervalYears);
}

void ComponentRecurringCost::resetCostIntervalYears() {
  setString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalYears,"");
}

bool ComponentRecurringCost::setCostIntervalMonths(int costIntervalMonths) {
  return setInt(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalMonths,costIntervalMonths);
}

void ComponentRecurringCost::resetCostIntervalMonths() {
  setString(OS_ComponentCost_LineItemExtensibleFields::RecurringCostIntervalMonths,"");
}

ComponentRecurringCost::ComponentRecurringCost(boost::shared_ptr<detail::ComponentCostLineItem_Impl> impl,unsigned index)
  : ModelExtensibleGroup(impl,index)
{}


/// ComponentCostLineItem
ComponentCostLineItem::ComponentCostLineItem(const ModelObject& modelObject)
  : ModelObject(ComponentCostLineItem::iddObjectType(), modelObject.model())
{
  BOOST_ASSERT(getImpl<detail::ComponentCostLineItem_Impl>());
  bool test = getImpl<detail::ComponentCostLineItem_Impl>()->setPointer(OS_ComponentCost_LineItemFields::ItemName, modelObject.handle());
  BOOST_ASSERT(test);

  if (modelObject.optionalCast<ConstructionBase>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Construction");
    BOOST_ASSERT(test);
  }else if (modelObject.optionalCast<Lights>() || modelObject.optionalCast<LightsDefinition>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Lights");
    BOOST_ASSERT(test);
  }else if (modelObject.optionalCast<ElectricEquipment>() || modelObject.optionalCast<ElectricEquipmentDefinition>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Equipment");
    BOOST_ASSERT(test);
  }else if (modelObject.optionalCast<GasEquipment>() || modelObject.optionalCast<GasEquipmentDefinition>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Equipment");
    BOOST_ASSERT(test);
  }else if (modelObject.optionalCast<HotWaterEquipment>() || modelObject.optionalCast<HotWaterEquipmentDefinition>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Equipment");
    BOOST_ASSERT(test);
  }else if (modelObject.optionalCast<SteamEquipment>() || modelObject.optionalCast<SteamEquipmentDefinition>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Equipment");
    BOOST_ASSERT(test);
  }else if (modelObject.optionalCast<Building>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Building");
    BOOST_ASSERT(test);
  }else if (modelObject.optionalCast<DaylightingControl>()){
    bool test = setString(OS_ComponentCost_LineItemFields::LineItemType, "Daylighting:Controls");
    BOOST_ASSERT(test);

    // TODO: add coils

  }else{
    throw openstudio::Exception("Cannot add cost to unknown model object type '" + modelObject.iddObject().name() + "'");
  }

}

// constructor
ComponentCostLineItem::ComponentCostLineItem(boost::shared_ptr<detail::ComponentCostLineItem_Impl> impl)
  : ModelObject(impl)
{}


IddObjectType ComponentCostLineItem::iddObjectType() 
{
  IddObjectType result(IddObjectType::OS_ComponentCost_LineItem);
  return result;
}

std::vector<std::string> ComponentCostLineItem::validLineItemTypeValues() 
{
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_ComponentCost_LineItemFields::LineItemType);
}

std::vector<std::string> ComponentCostLineItem::validMaterialCostUnitsValues() const
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->validMaterialCostUnitsValues();
}

std::vector<std::string> ComponentCostLineItem::validInstallationCostUnitsValues() const
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->validInstallationCostUnitsValues();
}

std::vector<std::string> ComponentCostLineItem::validDemolitionCostUnitsValues() const
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->validDemolitionCostUnitsValues();
}

std::vector<std::string> ComponentCostLineItem::validSalvageValueUnitsValues() const
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->validSalvageValueUnitsValues();
}

std::vector<std::string> ComponentCostLineItem::validRecurringCostUnitsValues() const
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->validRecurringCostUnitsValues();
}

std::string ComponentCostLineItem::lineItemType() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->lineItemType();
}

ModelObject ComponentCostLineItem::item() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->item();
}

boost::optional<double> ComponentCostLineItem::materialCost() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->materialCost();
}

boost::optional<std::string> ComponentCostLineItem::materialCostUnits() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->materialCostUnits();
}

boost::optional<double> ComponentCostLineItem::installationCost() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->installationCost();
}

boost::optional<std::string> ComponentCostLineItem::installationCostUnits() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->installationCostUnits();
}

boost::optional<int> ComponentCostLineItem::expectedLife() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->expectedLife();
}

boost::optional<double> ComponentCostLineItem::demolitionCost() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->demolitionCost();
}

boost::optional<std::string> ComponentCostLineItem::demolitionCostUnits() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->demolitionCostUnits();
}

boost::optional<double> ComponentCostLineItem::salvageValue() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->salvageValue();
}

boost::optional<std::string> ComponentCostLineItem::salvageValueUnits() const {
  return getImpl<detail::ComponentCostLineItem_Impl>()->salvageValueUnits();
}

std::vector<ComponentRecurringCost> ComponentCostLineItem::componentRecurringCosts() const
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->componentRecurringCosts();
}

bool ComponentCostLineItem::setMaterialCost(double materialCost) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setMaterialCost(materialCost);
}

void ComponentCostLineItem::resetMaterialCost() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetMaterialCost();
}

bool ComponentCostLineItem::setMaterialCostUnits(const std::string& materialCostUnits) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setMaterialCostUnits(materialCostUnits);
}

void ComponentCostLineItem::resetMaterialCostUnits() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetMaterialCostUnits();
}

bool ComponentCostLineItem::setInstallationCost(double installationCost) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setInstallationCost(installationCost);
}

void ComponentCostLineItem::resetInstallationCost() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetInstallationCost();
}

bool ComponentCostLineItem::setInstallationCostUnits(const std::string& installationCostUnits) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setInstallationCostUnits(installationCostUnits);
}

void ComponentCostLineItem::resetInstallationCostUnits() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetInstallationCostUnits();
}

bool ComponentCostLineItem::setExpectedLife(int expectedLife) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setExpectedLife(expectedLife);
}

void ComponentCostLineItem::resetExpectedLife() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetExpectedLife();
}

bool ComponentCostLineItem::setDemolitionCost(double demolitionCost) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setDemolitionCost(demolitionCost);
}

void ComponentCostLineItem::resetDemolitionCost() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetDemolitionCost();
}

bool ComponentCostLineItem::setDemolitionCostUnits(const std::string& demolitionCostUnits) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setDemolitionCostUnits(demolitionCostUnits);
}

void ComponentCostLineItem::resetDemolitionCostUnits() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetDemolitionCostUnits();
}

bool ComponentCostLineItem::setSalvageValue(double salvageValue) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setSalvageValue(salvageValue);
}

void ComponentCostLineItem::resetSalvageValue() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetSalvageValue();
}

bool ComponentCostLineItem::setSalvageValueUnits(const std::string& salvageValueUnits) {
  return getImpl<detail::ComponentCostLineItem_Impl>()->setSalvageValueUnits(salvageValueUnits);
}

void ComponentCostLineItem::resetSalvageValueUnits() {
  getImpl<detail::ComponentCostLineItem_Impl>()->resetSalvageValueUnits();
}

void ComponentCostLineItem::clearComponentRecurringCosts()
{
  getImpl<detail::ComponentCostLineItem_Impl>()->clearComponentRecurringCosts();
}

boost::optional<ComponentRecurringCost> ComponentCostLineItem::addComponentRecurringCost(const std::string& name,
  const std::string& costType, double cost, const std::string& costUnits)
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->addComponentRecurringCost(name, costType, cost, costUnits);
}


void ComponentCostLineItem::copyCosts(const ComponentCostLineItem& otherLineItem)
{
  getImpl<detail::ComponentCostLineItem_Impl>()->copyCosts(otherLineItem);
}

boost::optional<double> ComponentCostLineItem::costedArea() const
{
  return getImpl<detail::ComponentCostLineItem_Impl>()->costedArea();
}

void ComponentCostLineItem::hardSizeCostPerArea(bool hardSizeOnlyNonCapitalCosts)
{
  getImpl<detail::ComponentCostLineItem_Impl>()->hardSizeCostPerArea(hardSizeOnlyNonCapitalCosts);
}

void ComponentCostLineItem::hardSizeCostPerArea(double area, bool hardSizeOnlyNonCapitalCosts)
{
  getImpl<detail::ComponentCostLineItem_Impl>()->hardSizeCostPerArea(area, hardSizeOnlyNonCapitalCosts);
}

} // model
} // openstudio

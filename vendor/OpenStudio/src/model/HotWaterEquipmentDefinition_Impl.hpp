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

#ifndef MODEL_HOTWATEREQUIPMENTDEFINITION_IMPL_HPP
#define MODEL_HOTWATEREQUIPMENTDEFINITION_IMPL_HPP

#include "ModelAPI.hpp"
#include "SpaceLoadDefinition_Impl.hpp"

namespace openstudio {
namespace model {

class HotWaterEquipmentDefinition;

namespace detail {

  /** HotWaterEquipmentDefinition_Impl is a SpaceLoadDefinition_Impl that is the implementation class for HotWaterEquipmentDefinition.*/
  class MODEL_API HotWaterEquipmentDefinition_Impl : public SpaceLoadDefinition_Impl {
    Q_OBJECT;
    Q_PROPERTY(std::string designLevelCalculationMethod READ designLevelCalculationMethod);
    Q_PROPERTY(boost::optional<double> designLevel READ designLevel WRITE setDesignLevel);
    Q_PROPERTY(boost::optional<double> wattsperSpaceFloorArea READ wattsperSpaceFloorArea WRITE setWattsperSpaceFloorArea);
    Q_PROPERTY(boost::optional<double> wattsperPerson READ wattsperPerson WRITE setWattsperPerson);
    Q_PROPERTY(double fractionLatent READ fractionLatent WRITE setFractionLatent RESET resetFractionLatent);
    Q_PROPERTY(bool isFractionLatentDefaulted READ isFractionLatentDefaulted);
    Q_PROPERTY(double fractionRadiant READ fractionRadiant WRITE setFractionRadiant RESET resetFractionRadiant);
    Q_PROPERTY(bool isFractionRadiantDefaulted READ isFractionRadiantDefaulted);
    Q_PROPERTY(double fractionLost READ fractionLost WRITE setFractionLost RESET resetFractionLost);
    Q_PROPERTY(bool isFractionLostDefaulted READ isFractionLostDefaulted);
   public:
    /** @name Constructors and Destructors */
    //@{

    HotWaterEquipmentDefinition_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

    HotWaterEquipmentDefinition_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                     Model_Impl* model,
                                     bool keepHandle);

    HotWaterEquipmentDefinition_Impl(const HotWaterEquipmentDefinition_Impl& other,
                                     Model_Impl* model,
                                     bool keepHandle);

    virtual ~HotWaterEquipmentDefinition_Impl() {}

    //@}
    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    /** @name Getters */
    //@{

    std::string designLevelCalculationMethod() const;

    boost::optional<double> designLevel() const;

    boost::optional<double> wattsperSpaceFloorArea() const;

    boost::optional<double> wattsperPerson() const;

    double fractionLatent() const;

    bool isFractionLatentDefaulted() const;

    double fractionRadiant() const;

    bool isFractionRadiantDefaulted() const;

    double fractionLost() const;

    bool isFractionLostDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    /// Sets designLevelCalculationMethod to 'DesignLevel', clears wattsperSpaceFloorArea
    /// and wattsperPerson, and sets designLevel.
    bool setDesignLevel(boost::optional<double> designLevel);

    /// Sets designLevelCalculationMethod to 'Watts/Area', clears designLevel
    /// and wattsperPerson, and sets wattsperSpaceFloorArea.
    bool setWattsperSpaceFloorArea(boost::optional<double> wattsperSpaceFloorArea);

    /// Sets designLevelCalculationMethod to 'Watts/Person', clears designLevel
    /// and wattsperSpaceFloorArea, and sets wattsperPerson.
    bool setWattsperPerson(boost::optional<double> wattsperPerson);

    bool setFractionLatent(double fractionLatent);

    void resetFractionLatent();

    bool setFractionRadiant(double fractionRadiant);

    void resetFractionRadiant();

    bool setFractionLost(double fractionLost);

    void resetFractionLost();

    //@}
    /** @name Other */
    //@{

    /** Returns the design level represented by this definition, assuming floorArea (m^2) and 
     *  numPeople. */
    double getDesignLevel(double floorArea, double numPeople) const;

    /** Returns the watts/m^2 represented by this definition, assuming floorArea (m^2) and 
     *  numPeople. */
    double getPowerPerFloorArea(double floorArea, double numPeople) const;

    /** Returns the watts/person represented by this definition, assuming floorArea (m^2) and 
     *  numPeople. */
    double getPowerPerPerson(double floorArea, double numPeople) const;
   
    /** If method is a \link validDesignLevelCalculationMethodValues valid design level 
     *  calculation method \endlink, changes this definition to an equivalent power level, under 
     *  the assumptions of floorArea (m^2) and numPeople. */
    bool setDesignLevelCalculationMethod(const std::string& method, 
                                         double floorArea, 
                                         double numPeople);

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.HotWaterEquipmentDefinition");
  };

} // detail

} // model
} // openstudio

#endif // MODEL_HOTWATEREQUIPMENTDEFINITION_IMPL_HPP


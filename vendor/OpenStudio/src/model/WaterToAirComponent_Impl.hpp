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

#ifndef MODEL_WATERTOAIRCOMPONENT_IMPL_HPP
#define MODEL_WATERTOAIRCOMPONENT_IMPL_HPP

#include "HVACComponent_Impl.hpp"

namespace openstudio {

namespace model {

class ControllerWaterCoil;

namespace detail {

class MODEL_API WaterToAirComponent_Impl : public HVACComponent_Impl {
 public:

  WaterToAirComponent_Impl(IddObjectType type, Model_Impl* model);

  WaterToAirComponent_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

  WaterToAirComponent_Impl(const openstudio::detail::WorkspaceObject_Impl& other, 
                         Model_Impl* model, 
                         bool keepHandle);

  WaterToAirComponent_Impl(const WaterToAirComponent_Impl& other, Model_Impl* model, bool keepHandles);

  virtual ~WaterToAirComponent_Impl() {}

  virtual boost::optional<ModelObject> airInletModelObject();

  virtual boost::optional<ModelObject> airOutletModelObject();

  virtual boost::optional<ModelObject> waterInletModelObject();

  virtual boost::optional<ModelObject> waterOutletModelObject();

  virtual std::vector<HVACComponent> edges(const boost::optional<HVACComponent> & previous) override;

  virtual boost::optional<AirLoopHVAC> airLoopHVAC() const override;

  virtual boost::optional<PlantLoop> plantLoop() const override;

  virtual boost::optional<Loop> loop() const override;

  virtual unsigned airInletPort() = 0;
   
  virtual unsigned airOutletPort() = 0;
   
  virtual unsigned waterInletPort() = 0;
   
  virtual unsigned waterOutletPort() = 0;

  virtual bool addToNode(Node & node) override;

  virtual bool addToSplitter(Splitter & splitter) override;

  virtual std::vector<openstudio::IdfObject> remove() override;

  virtual ModelObject clone(Model model) const override;

  virtual void disconnectWaterSide();

  virtual void disconnectAirSide();

  virtual void disconnect() override;

  virtual bool removeFromAirLoopHVAC();

  virtual bool removeFromPlantLoop();

  boost::optional<ControllerWaterCoil> controllerWaterCoil();
 private:
  REGISTER_LOGGER("openstudio.model.WaterToAirComponent");
};

} // detail

} // model

} // openstudio

#endif


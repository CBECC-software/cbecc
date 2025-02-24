/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "ModelFixture.hpp"
#include "../AirTerminalSingleDuctParallelPIUReheat.hpp"
#include "../AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"
#include "../ScheduleRuleset.hpp"
#include "../ScheduleRuleset_Impl.hpp"
#include "../FanConstantVolume.hpp"
#include "../CoilHeatingElectric.hpp"
#include "../Schedule.hpp"
#include "../AirLoopHVAC.hpp"
#include "../PlantLoop.hpp"
#include "../Node.hpp"
#include "../Node_Impl.hpp"
#include "../ThermalZone.hpp"
#include "../ThermalZone_Impl.hpp"
#include "../PortList.hpp"
#include "../PortList_Impl.hpp"
#include "../AirLoopHVACZoneSplitter.hpp"

using namespace openstudio::model;

TEST_F(ModelFixture, AirTerminalSingleDuctParallelPIUReheat_AirTerminalSingleDuctParallelPIUReheat) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model m;
      Schedule s = m.alwaysOnDiscreteSchedule();
      FanConstantVolume piuFan = FanConstantVolume(m, s);
      CoilHeatingElectric piuReheatCoil = CoilHeatingElectric(m, s);
      AirTerminalSingleDuctParallelPIUReheat testObject(m, s, piuFan, piuReheatCoil);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");
}

TEST_F(ModelFixture, AirTerminalSingleDuctParallelPIUReheat_addToNode) {
  Model m;
  Schedule s = m.alwaysOnDiscreteSchedule();
  FanConstantVolume piuFan = FanConstantVolume(m, s);
  CoilHeatingElectric piuReheatCoil = CoilHeatingElectric(m, s);
  AirTerminalSingleDuctParallelPIUReheat testObject(m, s, piuFan, piuReheatCoil);

  AirLoopHVAC airLoop(m);

  Node supplyOutletNode = airLoop.supplyOutletNode();

  EXPECT_FALSE(testObject.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)2, airLoop.supplyComponents().size());

  Node inletNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();

  EXPECT_TRUE(testObject.addToNode(inletNode));
  EXPECT_EQ((unsigned)7, airLoop.demandComponents().size());

  PlantLoop plantLoop(m);
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(testObject.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)5, plantLoop.supplyComponents().size());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(testObject.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)5, plantLoop.demandComponents().size());

  AirTerminalSingleDuctParallelPIUReheat testObjectClone = testObject.clone(m).cast<AirTerminalSingleDuctParallelPIUReheat>();
  inletNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();

  EXPECT_FALSE(testObjectClone.addToNode(inletNode));
  EXPECT_TRUE(airLoop.addBranchForHVACComponent(testObjectClone));
  EXPECT_EQ((unsigned)10, airLoop.demandComponents().size());
}

TEST_F(ModelFixture, AirTerminalSingleDuctParallelPIUReheat) {
  // test that setAvailabilitySchedule also set PIU fan schedule
  {
    Model m;
    Schedule schedule = m.alwaysOnDiscreteSchedule();
    FanConstantVolume fan(m, schedule);
    CoilHeatingElectric coil(m, schedule);
    AirTerminalSingleDuctParallelPIUReheat terminal(m, schedule, fan, coil);

    AirLoopHVAC airLoopHVAC(m);
    airLoopHVAC.addBranchForHVACComponent(terminal);

    ScheduleRuleset hvacSchedule(m);
    airLoopHVAC.setAvailabilitySchedule(hvacSchedule);

    auto fanSchedule = fan.availabilitySchedule();
    ASSERT_EQ(hvacSchedule.handle(), fanSchedule.handle());
  }

  // test that addToNode (by proxy addBranchForZone) sets the fan schedule to match system availabilitySchedule
  {
    Model m;
    Schedule schedule = m.alwaysOnDiscreteSchedule();
    FanConstantVolume fan(m, schedule);
    CoilHeatingElectric coil(m, schedule);
    AirTerminalSingleDuctParallelPIUReheat terminal(m, schedule, fan, coil);

    AirLoopHVAC airLoopHVAC(m);

    ScheduleRuleset hvacSchedule(m);
    airLoopHVAC.setAvailabilitySchedule(hvacSchedule);

    ThermalZone zone(m);
    // KSB: I don't think it is the greatest idea to test these private methods,
    // but this area has resulted in a simulation error so it needs to be tested
    EXPECT_FALSE(zone.getImpl<detail::ThermalZone_Impl>()->exhaustPortList().getTarget(3));
    EXPECT_FALSE(zone.getImpl<detail::ThermalZone_Impl>()->inletPortList().getTarget(3));

    airLoopHVAC.addBranchForZone(zone, terminal);
    auto fanSchedule = fan.availabilitySchedule();
    ASSERT_EQ(hvacSchedule.handle(), fanSchedule.handle());

    EXPECT_TRUE(zone.getImpl<detail::ThermalZone_Impl>()->exhaustPortList().getTarget(3));
    EXPECT_TRUE(zone.getImpl<detail::ThermalZone_Impl>()->inletPortList().getTarget(3));

    EXPECT_EQ(9u, airLoopHVAC.demandComponents().size());
    EXPECT_EQ(1u, zone.equipment().size());

    auto zoneImpl = zone.getImpl<openstudio::model::detail::ThermalZone_Impl>();
    auto exhaustMo = zoneImpl->exhaustPortList().lastModelObject();
    ASSERT_TRUE(exhaustMo);
    auto exhaustNode = exhaustMo->optionalCast<Node>();
    ASSERT_TRUE(exhaustNode);
    ASSERT_TRUE(exhaustNode->outletModelObject());
    ASSERT_EQ(terminal, exhaustNode->outletModelObject().get());

    terminal.remove();

    EXPECT_FALSE(zone.getImpl<detail::ThermalZone_Impl>()->exhaustPortList().getTarget(3));
    EXPECT_TRUE(zone.getImpl<detail::ThermalZone_Impl>()->inletPortList().getTarget(3));

    EXPECT_EQ(7u, airLoopHVAC.demandComponents().size());
    EXPECT_TRUE(zone.equipment().empty());

    EXPECT_FALSE(zoneImpl->exhaustPortList().lastModelObject());
  }
}

TEST_F(ModelFixture, AirTerminalSingleDuctParallelPIUReheat_connectSecondaryAirInlet_regularCase_2033) {

  // Test for #2033
  // Base case: works fine
  Model m;
  Schedule schedule = m.alwaysOnDiscreteSchedule();
  FanConstantVolume fan(m, schedule);
  CoilHeatingElectric coil(m, schedule);
  AirTerminalSingleDuctParallelPIUReheat atu(m, schedule, fan, coil);

  ThermalZone zone(m);
  AirLoopHVAC airLoopHVAC(m);

  EXPECT_FALSE(atu.secondaryAirInletNode());
  EXPECT_FALSE(zone.exhaustPortList().lastModelObject());

  // Connect simulateanously the branch and atu
  EXPECT_TRUE(airLoopHVAC.addBranchForZone(zone, atu));

  ASSERT_TRUE(atu.secondaryAirInletNode());
  ASSERT_TRUE(zone.exhaustPortList().lastModelObject());
  EXPECT_EQ(atu.secondaryAirInletNode().get(), zone.exhaustPortList().lastModelObject().get());
}

TEST_F(ModelFixture, AirTerminalSingleDuctParallelPIUReheat_connectSecondaryAirInlet_atuFirst_2033) {

  // Test for #2033: When you connect the atu first, then add a zone it should work as well.
  Model m;
  Schedule schedule = m.alwaysOnDiscreteSchedule();
  FanConstantVolume fan(m, schedule);
  CoilHeatingElectric coil(m, schedule);
  AirTerminalSingleDuctParallelPIUReheat atu(m, schedule, fan, coil);

  AirLoopHVAC airLoopHVAC(m);

  // Connect atu only first
  airLoopHVAC.addBranchForHVACComponent(atu);
  EXPECT_FALSE(atu.secondaryAirInletNode());

  // First zone: this is the problematic case
  {
    ThermalZone zone(m);
    EXPECT_FALSE(zone.exhaustPortList().lastModelObject());

    // Now add zone (this was the problematic case)
    EXPECT_TRUE(airLoopHVAC.addBranchForZone(zone));
    ASSERT_TRUE(atu.secondaryAirInletNode());  // <===== Actual test is here
    ASSERT_TRUE(zone.exhaustPortList().lastModelObject());
    EXPECT_EQ(atu.secondaryAirInletNode().get(), zone.exhaustPortList().lastModelObject().get());
  }

  // Should work for any zone added after that too
  {
    ThermalZone zone(m);
    EXPECT_FALSE(zone.exhaustPortList().lastModelObject());

    // Now add zone (this was the problematic case)
    EXPECT_TRUE(airLoopHVAC.addBranchForZone(zone));

    // Get the cloned ATU
    ASSERT_EQ(1u, zone.equipment().size());
    auto _atu = zone.equipment()[0].optionalCast<AirTerminalSingleDuctParallelPIUReheat>();
    ASSERT_TRUE(_atu);

    ASSERT_TRUE(_atu->secondaryAirInletNode());
    ASSERT_TRUE(zone.exhaustPortList().lastModelObject());
    EXPECT_EQ(_atu->secondaryAirInletNode().get(), zone.exhaustPortList().lastModelObject().get());
  }
}

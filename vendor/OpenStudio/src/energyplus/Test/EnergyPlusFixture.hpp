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

#ifndef ENERGYPLUS_TEST_ENERGYPLUSFIXTURE_HPP
#define ENERGYPLUS_TEST_ENERGYPLUSFIXTURE_HPP

#include <gtest/gtest.h>

#include "../../utilities/core/Logger.hpp"
#include "../../utilities/core/FileLogSink.hpp"
#include "../../utilities/core/Path.hpp"

#include <vector>
#include <string>

class EnergyPlusFixture : public ::testing::Test {
 protected:
  /// initialize for each test
  virtual void SetUp() override;

  /// tear down after each test
  virtual void TearDown() override;

  /// initialize static members
  static void SetUpTestCase();

  /// tear down static members
  static void TearDownTestCase();

  REGISTER_LOGGER("EnergyPlusFixture");

  // static variables
  static boost::optional<openstudio::FileLogSink> logFile;

  typedef std::pair<openstudio::path,std::string> ComponentDirectoryAndType;
  static std::vector<ComponentDirectoryAndType> idfComponents;
};

#endif // ENERGYPLUS_TEST_ENERGYPLUSFIXTURE_HPP


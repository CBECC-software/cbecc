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

#ifndef MODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMAXIMUM_HPP
#define MODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMAXIMUM_HPP

#include "ModelAPI.hpp"
#include "SetpointManager.hpp"

namespace openstudio {
namespace model {

class ThermalZone;
class Node;

namespace detail {

  class SetpointManagerSingleZoneHumidityMaximum_Impl;

} // detail

/** SetpointManagerSingleZoneHumidityMaximum is a SetpointManager that wraps the OpenStudio IDD object 'OS:SetpointManager:SingleZone:Humidity:Maximum'. */
class MODEL_API SetpointManagerSingleZoneHumidityMaximum : public SetpointManager {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit SetpointManagerSingleZoneHumidityMaximum(const Model& model);

  virtual ~SetpointManagerSingleZoneHumidityMaximum() {}

  //@}

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();

  /** @name Getters */
  //@{

  std::string controlVariable() const;

  boost::optional<ThermalZone> controlZone() const;

  boost::optional<Node> setpointNode() const;

  //@}
  /** @name Setters */
  //@{

  bool setControlVariable(const std::string& controlVariable);

  bool setControlZone(const ThermalZone& thermalZone);

  void resetControlZone();

  //@}
  /** @name Other */
  //@{

  //@}
 protected:
  /// @cond
  typedef detail::SetpointManagerSingleZoneHumidityMaximum_Impl ImplType;

  explicit SetpointManagerSingleZoneHumidityMaximum(std::shared_ptr<detail::SetpointManagerSingleZoneHumidityMaximum_Impl> impl);

  friend class detail::SetpointManagerSingleZoneHumidityMaximum_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.SetpointManagerSingleZoneHumidityMaximum");
};

/** \relates SetpointManagerSingleZoneHumidityMaximum*/
typedef boost::optional<SetpointManagerSingleZoneHumidityMaximum> OptionalSetpointManagerSingleZoneHumidityMaximum;

/** \relates SetpointManagerSingleZoneHumidityMaximum*/
typedef std::vector<SetpointManagerSingleZoneHumidityMaximum> SetpointManagerSingleZoneHumidityMaximumVector;

} // model
} // openstudio

#endif // MODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMAXIMUM_HPP


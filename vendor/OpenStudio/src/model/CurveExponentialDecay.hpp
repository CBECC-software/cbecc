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

#ifndef MODEL_CURVEEXPONENTIALDECAY_HPP
#define MODEL_CURVEEXPONENTIALDECAY_HPP

#include "ModelAPI.hpp"
#include "Curve.hpp"

namespace openstudio {
namespace model {

namespace detail {

  class CurveExponentialDecay_Impl;

} // detail

/** CurveExponentialDecay is a Curve that wraps the OpenStudio IDD object 
 *  'OS:Curve:ExponentialDecay'. The functional form is \f$f(x) = c_1 + c_2 \cdot e^{c_3 \cdot x}\f$ */
class MODEL_API CurveExponentialDecay : public Curve {
 public:

  /** @name Constructors and Destructors */
  //@{

  /** Sets \f$c_1 = 0.0,\ c_2 = 1.0,\ c_3 = -1.0\f$, and bounds x within [0.0,1.0]. */
  explicit CurveExponentialDecay(const Model& model);

  virtual ~CurveExponentialDecay() {}

  //@}

  static IddObjectType iddObjectType();

  static std::vector<std::string> validInputUnitTypeforxValues();

  static std::vector<std::string> validOutputUnitTypeValues();

  /** @name Getters */
  //@{

  double coefficient1C1() const;

  double coefficient2C2() const;

  double coefficient3C3() const;

  double minimumValueofx() const;

  double maximumValueofx() const;

  boost::optional<double> minimumCurveOutput() const;

  boost::optional<double> maximumCurveOutput() const;

  std::string inputUnitTypeforx() const;

  bool isInputUnitTypeforxDefaulted() const;

  std::string outputUnitType() const;

  bool isOutputUnitTypeDefaulted() const;

  //@}
  /** @name Setters */
  //@{

  void setCoefficient1C1(double coefficient1C1);

  void setCoefficient2C2(double coefficient2C2);

  void setCoefficient3C3(double coefficient3C3);

  void setMinimumValueofx(double minimumValueofx);

  void setMaximumValueofx(double maximumValueofx);

  void setMinimumCurveOutput(double minimumCurveOutput);

  void resetMinimumCurveOutput();

  void setMaximumCurveOutput(double maximumCurveOutput);

  void resetMaximumCurveOutput();

  bool setInputUnitTypeforx(std::string inputUnitTypeforx);

  void resetInputUnitTypeforx();

  bool setOutputUnitType(std::string outputUnitType);

  void resetOutputUnitType();

  //@}
  /** @name Other */
  //@{

  //@}
 protected:
  /// @cond
  typedef detail::CurveExponentialDecay_Impl ImplType;

  explicit CurveExponentialDecay(std::shared_ptr<detail::CurveExponentialDecay_Impl> impl);

  friend class detail::CurveExponentialDecay_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  /// @endcond
 private:

  REGISTER_LOGGER("openstudio.model.CurveExponentialDecay");
};

/** \relates CurveExponentialDecay*/
typedef boost::optional<CurveExponentialDecay> OptionalCurveExponentialDecay;

/** \relates CurveExponentialDecay*/
typedef std::vector<CurveExponentialDecay> CurveExponentialDecayVector;

} // model
} // openstudio

#endif // MODEL_CURVEEXPONENTIALDECAY_HPP


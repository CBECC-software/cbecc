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

#ifndef MODEL_CURVEFANPRESSURERISE_IMPL_HPP
#define MODEL_CURVEFANPRESSURERISE_IMPL_HPP

#include "ModelAPI.hpp"
#include "Curve_Impl.hpp"

namespace openstudio {
namespace model {

namespace detail {

  /** CurveFanPressureRise_Impl is a Curve_Impl that is the implementation class for CurveFanPressureRise.*/
  class MODEL_API CurveFanPressureRise_Impl : public Curve_Impl {
    Q_OBJECT;
    Q_PROPERTY(double coefficient1C1 READ coefficient1C1 WRITE setCoefficient1C1);
    Q_PROPERTY(double coefficient2C2 READ coefficient2C2 WRITE setCoefficient2C2);
    Q_PROPERTY(double coefficient3C3 READ coefficient3C3 WRITE setCoefficient3C3);
    Q_PROPERTY(double coefficient4C4 READ coefficient4C4 WRITE setCoefficient4C4);
    Q_PROPERTY(double minimumValueofQfan READ minimumValueofQfan WRITE setMinimumValueofQfan);
    Q_PROPERTY(double maximumValueofQfan READ maximumValueofQfan WRITE setMaximumValueofQfan);
    Q_PROPERTY(double minimumValueofPsm READ minimumValueofPsm WRITE setMinimumValueofPsm);
    Q_PROPERTY(double maximumValueofPsm READ maximumValueofPsm WRITE setMaximumValueofPsm);
    Q_PROPERTY(boost::optional<double> minimumCurveOutput READ minimumCurveOutput WRITE setMinimumCurveOutput RESET resetMinimumCurveOutput);
    Q_PROPERTY(boost::optional<double> maximumCurveOutput READ maximumCurveOutput WRITE setMaximumCurveOutput RESET resetMaximumCurveOutput);
   public:

    /** @name Constructors and Destructors */
    //@{

    CurveFanPressureRise_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

    CurveFanPressureRise_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                              Model_Impl* model,
                              bool keepHandle);

    CurveFanPressureRise_Impl(const CurveFanPressureRise_Impl& other,
                              Model_Impl* model,
                              bool keepHandle);

    virtual ~CurveFanPressureRise_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual int numVariables() const override;

    virtual double evaluate(const std::vector<double>& x) const override;

    //@}
    /** @name Getters */
    //@{

    double coefficient1C1() const;

    double coefficient2C2() const;

    double coefficient3C3() const;

    double coefficient4C4() const;

    double minimumValueofQfan() const;

    double maximumValueofQfan() const;

    double minimumValueofPsm() const;

    double maximumValueofPsm() const;

    boost::optional<double> minimumCurveOutput() const;

    boost::optional<double> maximumCurveOutput() const;

    //@}
    /** @name Setters */
    //@{

    void setCoefficient1C1(double coefficient1C1);

    void setCoefficient2C2(double coefficient2C2);

    void setCoefficient3C3(double coefficient3C3);

    void setCoefficient4C4(double coefficient4C4);

    void setMinimumValueofQfan(double minimumValueofQfan);

    void setMaximumValueofQfan(double maximumValueofQfan);

    void setMinimumValueofPsm(double minimumValueofPsm);

    void setMaximumValueofPsm(double maximumValueofPsm);

    void setMinimumCurveOutput(boost::optional<double> minimumCurveOutput);

    void resetMinimumCurveOutput();

    void setMaximumCurveOutput(boost::optional<double> maximumCurveOutput);

    void resetMaximumCurveOutput();

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.CurveFanPressureRise");
  };

} // detail

} // model
} // openstudio

#endif // MODEL_CURVEFANPRESSURERISE_IMPL_HPP


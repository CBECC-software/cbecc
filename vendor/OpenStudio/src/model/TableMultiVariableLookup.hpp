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

#ifndef MODEL_TABLEMULTIVARIABLELOOKUP_HPP
#define MODEL_TABLEMULTIVARIABLELOOKUP_HPP

#include "ModelAPI.hpp"
#include "Curve.hpp"

#include "../utilities/math/FloatCompare.hpp"

namespace openstudio {

namespace model {

  namespace detail {

    class TableMultiVariableLookup_Impl;

  }  // namespace detail

  /** This class implements a single point of a TableMultiVariableLookup */
  class MODEL_API TableMultiVariableLookupPoint
  {
   public:
    TableMultiVariableLookupPoint(const std::vector<double>& x, double y);
    TableMultiVariableLookupPoint(double x1, double yValue);
    TableMultiVariableLookupPoint(double x1, double x2, double yValue);
    TableMultiVariableLookupPoint(double x1, double x2, double x3, double yValue);
    TableMultiVariableLookupPoint(double x1, double x2, double x3, double x4, double yValue);
    TableMultiVariableLookupPoint(double x1, double x2, double x3, double x4, double x5, double yValue);

    std::vector<double> x() const;
    double y() const;

    // this operator is to support sorting of TableMultiVariableLookupPoint in the order required by EnergyPlus Table:Lookup object
    bool operator<(const TableMultiVariableLookupPoint& other) const;

   private:
    std::vector<double> m_x;
    double m_y;
  };

  // Overload operator<<
  MODEL_API std::ostream& operator<<(std::ostream& out, const openstudio::model::TableMultiVariableLookupPoint& point);

  /** TableMultiVariableLookup is a Curve that wraps the OpenStudio IDD object 'OS:Table:MultiVariableLookup'. */
  class MODEL_API TableMultiVariableLookup : public Curve
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    /** Create a TableMultiVariableLookup object with the specified number
    * of independent variables.
    */
    explicit TableMultiVariableLookup(const Model& model, const int& numberofIndependentVariables);

    virtual ~TableMultiVariableLookup() {}

    //@}

    static IddObjectType iddObjectType();

    static std::vector<std::string> interpolationMethodValues();

    static std::vector<std::string> curveTypeValues();

    static std::vector<std::string> tableDataFormatValues();

    static std::vector<std::string> x1SortOrderValues();

    static std::vector<std::string> x2SortOrderValues();

    static std::vector<std::string> inputUnitTypeforX1Values();

    static std::vector<std::string> inputUnitTypeforX2Values();

    static std::vector<std::string> inputUnitTypeforX3Values();

    static std::vector<std::string> inputUnitTypeforX4Values();

    static std::vector<std::string> inputUnitTypeforX5Values();

    static std::vector<std::string> outputUnitTypeValues();

    /** @name Getters */
    //@{

    std::string interpolationMethod() const;

    bool isInterpolationMethodDefaulted() const;

    int numberofInterpolationPoints() const;

    bool isNumberofInterpolationPointsDefaulted() const;

    boost::optional<std::string> curveType() const;

    std::string tableDataFormat() const;

    bool isTableDataFormatDefaulted() const;

    boost::optional<double> normalizationReference() const;

    boost::optional<double> minimumValueofX1() const;

    boost::optional<double> maximumValueofX1() const;

    boost::optional<double> minimumValueofX2() const;

    boost::optional<double> maximumValueofX2() const;

    boost::optional<double> minimumValueofX3() const;

    boost::optional<double> maximumValueofX3() const;

    boost::optional<double> minimumValueofX4() const;

    boost::optional<double> maximumValueofX4() const;

    boost::optional<double> minimumValueofX5() const;

    boost::optional<double> maximumValueofX5() const;

    boost::optional<double> minimumTableOutput() const;

    boost::optional<double> maximumTableOutput() const;

    std::string inputUnitTypeforX1() const;

    bool isInputUnitTypeforX1Defaulted() const;

    std::string inputUnitTypeforX2() const;

    bool isInputUnitTypeforX2Defaulted() const;

    std::string inputUnitTypeforX3() const;

    bool isInputUnitTypeforX3Defaulted() const;

    std::string inputUnitTypeforX4() const;

    bool isInputUnitTypeforX4Defaulted() const;

    std::string inputUnitTypeforX5() const;

    bool isInputUnitTypeforX5Defaulted() const;

    std::string outputUnitType() const;

    bool isOutputUnitTypeDefaulted() const;

    int numberofIndependentVariables() const;

    /** Print a fixed-width table of the points, precision is the number of decimals */
    std::string printTable(unsigned int precision = 3) const;

    //@}
    /** @name Setters */
    //@{

    bool setInterpolationMethod(const std::string& interpolationMethod);

    void resetInterpolationMethod();

    bool setNumberofInterpolationPoints(int numberofInterpolationPoints);

    void resetNumberofInterpolationPoints();

    bool setCurveType(const std::string& curveType);

    void resetCurveType();

    bool setTableDataFormat(const std::string& tableDataFormat);

    void resetTableDataFormat();

    bool setNormalizationReference(double normalizationReference);

    void resetNormalizationReference();

    bool setMinimumValueofX1(double minimumValueofX1);

    void resetMinimumValueofX1();

    bool setMaximumValueofX1(double maximumValueofX1);

    void resetMaximumValueofX1();

    bool setMinimumValueofX2(double minimumValueofX2);

    void resetMinimumValueofX2();

    bool setMaximumValueofX2(double maximumValueofX2);

    void resetMaximumValueofX2();

    bool setMinimumValueofX3(double minimumValueofX3);

    void resetMinimumValueofX3();

    bool setMaximumValueofX3(double maximumValueofX3);

    void resetMaximumValueofX3();

    bool setMinimumValueofX4(double minimumValueofX4);

    void resetMinimumValueofX4();

    bool setMaximumValueofX4(double maximumValueofX4);

    void resetMaximumValueofX4();

    bool setMinimumValueofX5(double minimumValueofX5);

    void resetMinimumValueofX5();

    bool setMaximumValueofX5(double maximumValueofX5);

    void resetMaximumValueofX5();

    bool setMinimumTableOutput(double minimumTableOutput);

    void resetMinimumTableOutput();

    bool setMaximumTableOutput(double maximumTableOutput);

    void resetMaximumTableOutput();

    bool setInputUnitTypeforX1(const std::string& inputUnitTypeforX1);

    void resetInputUnitTypeforX1();

    bool setInputUnitTypeforX2(const std::string& inputUnitTypeforX2);

    void resetInputUnitTypeforX2();

    bool setInputUnitTypeforX3(const std::string& inputUnitTypeforX3);

    void resetInputUnitTypeforX3();

    bool setInputUnitTypeforX4(const std::string& inputUnitTypeforX4);

    void resetInputUnitTypeforX4();

    bool setInputUnitTypeforX5(const std::string& inputUnitTypeforX5);

    void resetInputUnitTypeforX5();

    bool setOutputUnitType(const std::string& outputUnitType);

    void resetOutputUnitType();

    //@}
    /** @name Other */
    //@{

    // Primary way to add a point
    bool addPoint(const TableMultiVariableLookupPoint& point);

    /**
   * Add a y value corresponding to xValues. The size of the XValues vector must be
   * equal to the number of independent variables specified when the table was created.
   * If a y value already exists for a particular coordinate, then the y value
   * will be replaced.
   */
    bool addPoint(const std::vector<double>& xValues, double yValue);
    bool addPoint(double x1, double yValue);
    bool addPoint(double x1, double x2, double yValue);
    bool addPoint(double x1, double x2, double x3, double yValue);
    bool addPoint(double x1, double x2, double x3, double x4, double yValue);
    bool addPoint(double x1, double x2, double x3, double x4, double x5, double yValue);

    // Return a vector of points, this is the entire set of data points
    std::vector<TableMultiVariableLookupPoint> points() const;

    // Directly set the points from a vector, will delete any existing points
    bool setPoints(const std::vector<TableMultiVariableLookupPoint>& points);

    boost::optional<double> yValue(const std::vector<double>& xValues) const;

    /** Return all of the x values for independent variable i
    * in ascending order.
    *
    * The independent variables are indexed from 0.
    */
    std::vector<double> xValues(int i) const;

    /**
  * Synonym for numberofIndependentVariables.  This is inherited from the base class.
  */
    int numVariables() const;

    /**
  * Not supported.  This is inherited from the base class.
  */
    double evaluate(const std::vector<double>& x) const;

    //@}
   protected:
    /// @cond
    typedef detail::TableMultiVariableLookup_Impl ImplType;

    explicit TableMultiVariableLookup(std::shared_ptr<detail::TableMultiVariableLookup_Impl> impl);

    friend class detail::TableMultiVariableLookup_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.TableMultiVariableLookup");
  };

  /** \relates TableMultiVariableLookup*/
  typedef boost::optional<TableMultiVariableLookup> OptionalTableMultiVariableLookup;

  /** \relates TableMultiVariableLookup*/
  typedef std::vector<TableMultiVariableLookup> TableMultiVariableLookupVector;

  /** \relates TableMultiVariableLookupPoint*/
  typedef std::vector<TableMultiVariableLookupPoint> TableMultiVariableLookupPointVector;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_TABLEMULTIVARIABLELOOKUP_HPP

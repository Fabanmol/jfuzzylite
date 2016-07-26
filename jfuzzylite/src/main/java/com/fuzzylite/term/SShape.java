/*
 Copyright (C) 2010-2016 by FuzzyLite Limited.
 All rights reserved.

 This file is part of jfuzzylite(TM).

 jfuzzylite is free software: you can redistribute it and/or modify it under
 the terms of the FuzzyLite License included with the software.

 You should have received a copy of the FuzzyLite License along with
 jfuzzylite. If not, see <http://www.fuzzylite.com/license/>.

 fuzzylite(R) is a registered trademark of FuzzyLite Limited.
 jfuzzylite(TM) is a trademark of FuzzyLite Limited.

 */
package com.fuzzylite.term;

import com.fuzzylite.Op;
import java.util.Iterator;
import java.util.List;

public class SShape extends Term {

    private double start, end;

    public SShape() {
        this("");
    }

    public SShape(String name) {
        this(name, Double.NaN, Double.NaN);
    }

    public SShape(String name, double start, double end) {
        this(name, start, end, 1.0);
    }

    public SShape(String name, double start, double end, double height) {
        super(name, height);
        this.start = start;
        this.end = end;
    }

    @Override
    public String parameters() {
        return Op.join(" ", start, end)
                + (!Op.isEq(height, 1.0) ? " " + Op.str(height) : "");
    }

    @Override
    public void configure(String parameters) {
        if (parameters.isEmpty()) {
            return;
        }
        List<String> values = Op.split(parameters, " ");
        int required = 2;
        if (values.size() < required) {
            throw new RuntimeException(String.format(
                    "[configuration error] term <%s> requires <%d> parameters",
                    this.getClass().getSimpleName(), required));
        }
        Iterator<String> it = values.iterator();
        setStart(Op.toDouble(it.next()));
        setEnd(Op.toDouble(it.next()));
        if (values.size() > required) {
            setHeight(Op.toDouble(it.next()));
        }
    }

    @Override
    public double membership(double x) {
        if (Double.isNaN(x)) {
            return Double.NaN;
        }

        if (Op.isLE(x, start)) {
            return height * 0.0;
        } else if (Op.isLE(x, 0.5 * (start + end))) {
            return height * 2.0 * Math.pow((x - start) / (end - start), 2);
        } else if (Op.isLt(x, end)) {
            return height * (1.0 - 2.0 * Math.pow((x - end) / (end - start), 2));
        }

        return height * 1.0;
    }

    public double getStart() {
        return start;
    }

    public void setStart(double start) {
        this.start = start;
    }

    public double getEnd() {
        return end;
    }

    public void setEnd(double end) {
        this.end = end;
    }

    @Override
    public SShape clone() throws CloneNotSupportedException {
        return (SShape) super.clone();
    }

}

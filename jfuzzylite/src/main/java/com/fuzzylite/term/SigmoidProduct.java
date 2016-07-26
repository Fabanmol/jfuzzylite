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

public class SigmoidProduct extends Term {

    private double left, rising;
    private double falling, right;

    public SigmoidProduct() {
        this("");
    }

    public SigmoidProduct(String name) {
        this(name, Double.NaN, Double.NaN, Double.NaN, Double.NaN);
    }

    public SigmoidProduct(String name, double left, double rising,
            double falling, double right) {
        this(name, left, rising, falling, right, 1.0);
    }

    public SigmoidProduct(String name, double left, double rising,
            double falling, double right, double height) {
        super(name, height);
        this.left = left;
        this.rising = rising;
        this.falling = falling;
        this.right = right;
    }

    @Override
    public String parameters() {
        return Op.join(" ", left, rising, falling, right)
                + (!Op.isEq(height, 1.0) ? " " + Op.str(height) : "");
    }

    @Override
    public void configure(String parameters) {
        if (parameters.isEmpty()) {
            return;
        }
        List<String> values = Op.split(parameters, " ");
        int required = 4;
        if (values.size() < required) {
            throw new RuntimeException(String.format(
                    "[configuration error] term <%s> requires <%d> parameters",
                    this.getClass().getSimpleName(), required));
        }
        Iterator<String> it = values.iterator();
        setLeft(Op.toDouble(it.next()));
        setRising(Op.toDouble(it.next()));
        setFalling(Op.toDouble(it.next()));
        setRight(Op.toDouble(it.next()));
        if (values.size() > required) {
            setHeight(Op.toDouble(it.next()));
        }
    }

    @Override
    public double membership(double x) {
        if (Double.isNaN(x)) {
            return Double.NaN;
        }
        double a = 1.0 + Math.exp(-rising * (x - left));
        double b = 1.0 + Math.exp(-falling * (x - right));
        return height * 1.0 / (a * b);
    }

    public double getLeft() {
        return left;
    }

    public void setLeft(double left) {
        this.left = left;
    }

    public double getRising() {
        return rising;
    }

    public void setRising(double rising) {
        this.rising = rising;
    }

    public double getFalling() {
        return falling;
    }

    public void setFalling(double falling) {
        this.falling = falling;
    }

    public double getRight() {
        return right;
    }

    public void setRight(double right) {
        this.right = right;
    }

    @Override
    public SigmoidProduct clone() throws CloneNotSupportedException {
        return (SigmoidProduct) super.clone();
    }

}

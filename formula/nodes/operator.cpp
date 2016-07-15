/***************************************************************************
    *   Copyright (C) 2016 by Renaud Guezennec                                *
    *   http://www.rolisteam.org/contact                                      *
    *                                                                         *
    *   rolisteam is free software; you can redistribute it and/or modify     *
    *   it under the terms of the GNU General Public License as published by  *
    *   the Free Software Foundation; either version 2 of the License, or     *
    *   (at your option) any later version.                                   *
    *                                                                         *
    *   This program is distributed in the hope that it will be useful,       *
    *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
    *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
    *   GNU General Public License for more details.                          *
    *                                                                         *
    *   You should have received a copy of the GNU General Public License     *
    *   along with this program; if not, write to the                         *
    *   Free Software Foundation, Inc.,                                       *
    *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
    ***************************************************************************/
#include "operator.h"
namespace Formula
{
OperatorFNode::OperatorFNode()
{

}

ParsingToolFormula::FormulaOperator OperatorFNode::getOperator() const
{
    return m_operator;
}

void OperatorFNode::setOperator(const ParsingToolFormula::FormulaOperator &ope)
{
    m_operator= ope;
}

bool OperatorFNode::run(FormulaNode *previous)
{
    for(auto node : m_parameters)
    {
        if(NULL!=node)
        {
            node->run(this);
        }
    }

    switch(m_operator)
    {
    case ParsingToolFormula::MIN:
        min();
        break;
    case ParsingToolFormula::MAX:
        max();
        break;
    }
    if(NULL!=m_next)
    {
        m_next->run(this);
    }
    return true;
}

void OperatorFNode::addParameter(FormulaNode *node)
{
    m_parameters.append(node);
}

void OperatorFNode::min()
{
    QVariant min;
    for(int i = 0; i< m_parameters.size() ; ++i)
    {
        FormulaNode* node = m_parameters.at(i);
        node = getLatestNode(node);
        if(NULL!=node)
        {
            QVariant var = node->getResult();
            if(0==i)
            {
                min = var;
            }
            else if(var<min)
            {
                min = var;
            }
        }

    }
    m_result = min;
}
void OperatorFNode::max()
{
    QVariant max;
    for(int i = 0; i< m_parameters.size() ; ++i)
    {
        FormulaNode* node = m_parameters.at(i);
        node = getLatestNode(node);
        if(NULL!=node)
        {
            QVariant var = node->getResult();
            if(0==i)
            {
                var = max;
            }
            else if(var>max)
            {
                max = var;
            }
        }

    }
    m_result = max;
}

QVariant OperatorFNode::getResult()
{
    return m_result;
}

}

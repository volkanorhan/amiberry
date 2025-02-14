/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004, 2005, 2006, 2007 Olof Naessén and Per Larsson
 *
 *                                                         Js_./
 * Per Larsson a.k.a finalman                          _RqZ{a<^_aa
 * Olof Naessén a.k.a jansem/yakslem                _asww7!uY`>  )\a//
 *                                                 _Qhm`] _f "'c  1!5m
 * Visit: http://guichan.darkbits.org             )Qk<P ` _: :+' .'  "{[
 *                                               .)j(] .d_/ '-(  P .   S
 * License: (BSD)                                <Td/Z <fP"5(\"??"\a.  .L
 * Redistribution and use in source and          _dV>ws?a-?'      ._/L  #'
 * binary forms, with or without                 )4d[#7r, .   '     )d`)[
 * modification, are permitted provided         _Q-5'5W..j/?'   -?!\)cam'
 * that the following conditions are met:       j<<WP+k/);.        _W=j f
 * 1. Redistributions of source code must       .$%w\/]Q  . ."'  .  mj$
 *    retain the above copyright notice,        ]E.pYY(Q]>.   a     J@\
 *    this list of conditions and the           j(]1u<sE"L,. .   ./^ ]{a
 *    following disclaimer.                     4'_uomm\.  )L);-4     (3=
 * 2. Redistributions in binary form must        )_]X{Z('a_"a7'<a"a,  ]"[
 *    reproduce the above copyright notice,       #}<]m7`Za??4,P-"'7. ).m
 *    this list of conditions and the            ]d2e)Q(<Q(  ?94   b-  LQ/
 *    following disclaimer in the                <B!</]C)d_, '(<' .f. =C+m
 *    documentation and/or other materials      .Z!=J ]e []('-4f _ ) -.)m]'
 *    provided with the distribution.          .w[5]' _[ /.)_-"+?   _/ <W"
 * 3. Neither the name of Guichan nor the      :$we` _! + _/ .        j?
 *    names of its contributors may be used     =3)= _f  (_yQmWW$#(    "
 *    to endorse or promote products derived     -   W,  sQQQQmZQ#Wwa]..
 *    from this software without specific        (js, \[QQW$QWW#?!V"".
 *    prior written permission.                    ]y:.<\..          .
 *                                                 -]n w/ '         [.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT       )/ )/           !
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY         <  (; sac    ,    '
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING,               ]^ .-  %
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF            c <   r
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR            aga<  <La
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          5%  )P'-3L
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR        _bQf` y`..)a
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          ,J?4P'.P"_(\?d'.,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES               _Pa,)!f/<[]/  ?"
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT      _2-..:. .r+_,.. .
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     ?a.<%"'  " -'.a_ _,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION)                     ^
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * For comments regarding functions please see the header file.
 */

#include "guisan/widgets/container.hpp"

#include "guisan/exception.hpp"
#include "guisan/graphics.hpp"

namespace gcn
{

    Container::~Container()
    = default;

    void Container::draw(Graphics* graphics)
    {
        if (isOpaque())
        {
            graphics->setColor(getBaseColor());
            graphics->fillRectangle(Rectangle(0, 0, getWidth(), getHeight()));
        }
        drawChildren(graphics);
    }

    void Container::setOpaque(bool opaque)
    {
        mOpaque = opaque;
    }

    bool Container::isOpaque() const
    {
        return mOpaque;
    }

    void Container::add(Widget* widget)
    {
        Widget::add(widget);
        distributeWidgetAddedEvent(widget);
    }

    void Container::add(Widget* widget, int x, int y)
    {
        widget->setPosition(x, y);
        Widget::add(widget);
        distributeWidgetAddedEvent(widget);
    }

    void Container::remove(Widget* widget)
    {
        Widget::remove(widget);
        distributeWidgetRemovedEvent(widget);
    }

    void Container::clear()
    {
        Widget::clear();
    }

    Widget* Container::findWidgetById(const std::string &id)
    {
        return Widget::findWidgetById(id);
    }
    void Container::addContainerListener(ContainerListener* containerListener)
    {
        mContainerListeners.push_back(containerListener);
    }

    void Container::removeContainerListener(ContainerListener* containerListener)
    {
        mContainerListeners.remove(containerListener);
    }

    void Container::distributeWidgetAddedEvent(Widget* source)
    {
        const ContainerEvent event(source, this);

        for (ContainerListener* containerListener : mContainerListeners)
        {
            containerListener->widgetAdded(event);
        }
    }

    void Container::distributeWidgetRemovedEvent(Widget* source)
    {
        ContainerEvent event(source, this);

        for (ContainerListener* containerListener : mContainerListeners)
        {
            containerListener->widgetRemoved(event);
        }
    }

    const std::list<Widget*>& Container::getChildren() const
    {
        return Widget::getChildren();
    }

    void Container::resizeToContent()
    {
        Widget::resizeToChildren();
    }

    Rectangle Container::getChildrenArea()
    {
        return Rectangle(0, 0, getWidth(), getHeight());
    }

    void Container::drawChildren(Graphics* graphics)
    {
        graphics->pushClipArea(getChildrenArea());

        std::list<Widget*> children = getChildren();
        for (const auto& iter : children)
        {
            if (iter->isVisible())
            {
                // If the widget has a frame,
                // draw it before drawing the widget
                if (iter->getFrameSize() > 0)
                {
                    Rectangle rec = iter->getDimension();
                    rec.x -= static_cast<int>(iter->getFrameSize());
                    rec.y -= static_cast<int>(iter->getFrameSize());
                    rec.width += static_cast<int>(2 * iter->getFrameSize());
                    rec.height += static_cast<int>(2 * iter->getFrameSize());
                    graphics->pushClipArea(rec);
                    iter->drawFrame(graphics);
                    graphics->popClipArea();
                }
                graphics->pushClipArea(iter->getDimension());
                iter->draw(graphics);
                graphics->popClipArea();
            }
        }
        graphics->popClipArea();
    }
} // namespace gcn

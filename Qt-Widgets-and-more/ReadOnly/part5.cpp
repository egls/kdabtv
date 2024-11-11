/* MIT License

Copyright (C) 2023 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Form.h"
#include <QAbstractItemView>
#include <QDebug>
#include <QEvent>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QScrollBar>
#include <QTabBar>
#include <QTextEdit>

namespace {
// Taken from https://github.com/KDAB/KDAlgorithms
template <typename Value, typename ContainerValue>
bool value_in(Value &&value, std::initializer_list<ContainerValue> container)
{
    return std::find(std::cbegin(container), std::cend(container), std::forward<Value>(value))
        != std::cend(container);
}

class ReadOnlyHelper : public QObject
{
    Q_OBJECT
public:
    static ReadOnlyHelper &instance()
    {
        static ReadOnlyHelper instance;
        return instance;
    }

    void makeReadOnly(QWidget *widget)
    {
        if (auto edit = qobject_cast<QLineEdit *>(widget)) {
            edit->setReadOnly(true);
            return;
        }

        if (auto edit = qobject_cast<QTextEdit *>(widget)) {
            edit->setReadOnly(true);
            return;
        }

        if (auto edit = qobject_cast<QPlainTextEdit *>(widget)) {
            edit->setReadOnly(true);
            return;
        }

        if (qobject_cast<QTabBar *>(widget) || qobject_cast<QScrollBar *>(widget))
            return;

        widget->installEventFilter(this);

        const auto children =
            widget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);

        for (const auto child : children) {
            makeReadOnly(child);
        }
    }

protected:
    bool eventFilter(QObject *object, QEvent *event) override
    {
        if (value_in(event->type(),
                     {
                         QEvent::MouseButtonPress,
                         QEvent::MouseButtonRelease,
                         QEvent::MouseButtonDblClick,
                         QEvent::MouseMove,
                         QEvent::KeyPress,
                         QEvent::KeyRelease,
                     }))
            return true;
        if (event->type() == QEvent::Wheel
            && (!object->parent() || !object->parent()->inherits("QAbstractScrollArea")))
            return true;
        return false;
    }
};
} // end namespace

void part5()
{
    qDebug() << "========== ReadOnly - part5 ==========";
    auto form = new Form;
    ReadOnlyHelper::instance().makeReadOnly(form);
    form->show();
}

#include "part5.moc"

/**
 * Created by Maple on 8/2/15.
 */

var ModelBase = cc.Class.extend({
    ctor: function(id) {
        this._id = id;
        this._update(id);
    },
    getId: function() {
        return this._id;
    },
    _update: function(id) {
        cc.assert(false, "override me.");
    },
    _id: null,
    _scheme: null,
});
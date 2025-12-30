/*! For license information please see sc.js.LICENSE.txt */
!function(e,t){"object"==typeof exports&&"object"==typeof module?module.exports=t():"function"==typeof define&&define.amd?define([],t):"object"==typeof exports?exports.sc=t():e.sc=t()}(this,(()=>(()=>{"use strict";var e=[function(e,t,s){var n=this&&this.__createBinding||(Object.create?function(e,t,s,n){void 0===n&&(n=s);var r=Object.getOwnPropertyDescriptor(t,s);r&&!("get"in r?!t.__esModule:r.writable||r.configurable)||(r={enumerable:!0,get:function(){return t[s]}}),Object.defineProperty(e,n,r)}:function(e,t,s,n){void 0===n&&(n=s),e[n]=t[s]}),r=this&&this.__exportStar||function(e,t){for(var s in e)"default"===s||Object.prototype.hasOwnProperty.call(t,s)||n(t,e,s)};Object.defineProperty(t,"__esModule",{value:!0}),r(s(1),t),r(s(2),t),r(s(10),t),r(s(11),t),r(s(4),t),r(s(12),t),r(s(5),t),r(s(13),t),r(s(14),t),r(s(6),t),r(s(7),t),r(s(15),t),r(s(8),t),r(s(3),t)},(e,t)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.ScAddr=void 0,t.ScAddr=class{constructor(e=0){this._value=e}get value(){return this._value}isValid(){return 0!=this._value}equal(e){return this._value===e._value}}},function(e,t,s){var n=this&&this.__awaiter||function(e,t,s,n){return new(s||(s=Promise))((function(r,c){function o(e){try{i(n.next(e))}catch(e){c(e)}}function a(e){try{i(n.throw(e))}catch(e){c(e)}}function i(e){var t;e.done?r(e.value):(t=e.value,t instanceof s?t:new s((function(e){e(t)}))).then(o,a)}i((n=n.apply(e,t||[])).next())}))};Object.defineProperty(t,"__esModule",{value:!0}),t.ScClient=void 0;const r=s(3),c=s(1),o=s(4),a=s(5),i=s(6),_=s(7),p=s(9),d=s(8),l={keynodesCacheSize:d.DEFAULT_KEYNODES_CACHE_SIZE};t.ScClient=class{constructor(e,t=l){var s;this.sendMessagesFromQueue=()=>{this._messageQueue.forEach((e=>e())),this._messageQueue=[]},this.onMessage=e=>{var t;const s=JSON.parse(e.data.toString()),n=s.id,r=this._callbacks[n];if(s.event){const e=this._events[n];if(!e)throw`Can't find callback for an event ${n}`;null===(t=e.callback)||void 0===t||t.call(e,new c.ScAddr(s.payload[0]),new c.ScAddr(s.payload[1]),new c.ScAddr(s.payload[2]),e.id)}else{if(!r)throw`Can't find callback for a command ${n}`;delete this._callbacks[n],r(s)}},this._socket="string"==typeof e?new WebSocket(e):e,this._socket.onmessage=this.onMessage,this._socket.onopen=this.sendMessagesFromQueue,this._messageQueue=[],this._callbacks={},this._events={},this._eventID=1,this._keynodesCacheSize=null!==(s=t.keynodesCacheSize)&&void 0!==s?s:d.DEFAULT_KEYNODES_CACHE_SIZE,this._keynodesCache=new Map}addEventListener(e,t){this._socket.addEventListener(e,t)}removeEventListener(e,t){this._socket.removeEventListener(e,t)}sendMessage(e,t,s){if(this._eventID++,this._callbacks[this._eventID])throw"Invalid state of messages queue";this._callbacks[this._eventID]=s;const n=JSON.stringify({id:this._eventID,type:e,payload:t}),r=()=>this._socket.send(n);this._socket.readyState===this._socket.OPEN?r():this._messageQueue.push(r)}resolveOrReject(e,t,s,n){return 0===n.length?e(s):t("string"==typeof n?n:n.map((({message:e})=>e)))}getUser(){return n(this,void 0,void 0,(function*(){return new Promise(((e,t)=>{this.sendMessage("connection_info",null,(({payload:s,errors:n})=>{const r=new c.ScAddr(s.user_addr);this.resolveOrReject(e,t,r,n)}))}))}))}getElementsTypes(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{if(!e.length)return t([]);const n=e.map((({value:e})=>e));this.sendMessage("check_elements",n,(({payload:e,errors:n})=>{const r=e.map((e=>new _.ScType(e)));this.resolveOrReject(t,s,r,n)}))}))}))}checkElements(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `checkElements` method is deprecated. Use `getElementsTypes` instead."),this.getElementsTypes(e)}))}generateElements(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.commands.map((t=>t.type.isLink()?{el:"link",type:t.type.value,content:t.data.content,content_type:t.data.type}:t.type.isNode()?{el:"node",type:t.type.value}:t.type.isConnector()?{el:"edge",type:t.type.value,src:(0,p.transformConnectorInfo)(e,t.data.src),trg:(0,p.transformConnectorInfo)(e,t.data.trg)}:void(0,r.invalidValue)("Unknown type"))).filter((e=>Boolean(e)));this.sendMessage("create_elements",n,(({payload:e,errors:n})=>{const r=e.map((e=>new c.ScAddr(e)));this.resolveOrReject(t,s,r,n)}))}))}))}createElements(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `createElements` method is deprecated. Use `generateElements` instead."),this.generateElements(e)}))}generateElementsBySCs(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((e=>{var t;return"string"==typeof e?{scs:e,output_structure:0}:{scs:e.scs,output_structure:null===(t=e.output_structure)||void 0===t?void 0:t.value}}));this.sendMessage("create_elements_by_scs",n,(({payload:e,errors:n})=>{this.resolveOrReject(t,s,e,n)}))}))}))}createElementsBySCs(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `createElementsBySCs` method is deprecated. Use `generateElementsBySCs` instead."),this.generateElementsBySCs(e)}))}eraseElements(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((({value:e})=>e));this.sendMessage("delete_elements",n,(({status:e,errors:n})=>{this.resolveOrReject(t,s,e,n)}))}))}))}deleteElements(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `deleteElements` method is deprecated. Use `eraseElements` instead."),this.eraseElements(e)}))}setLinkContents(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((e=>{var t;return{command:"set",type:e.typeToStr(),data:e.data,addr:null===(t=e.addr)||void 0===t?void 0:t.value}}));this.sendMessage("content",n,(({payload:e,errors:n})=>{this.resolveOrReject(t,s,e,n)}))}))}))}getLinkContents(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((({value:e})=>({command:"get",addr:e})));this.sendMessage("content",n,(({payload:e,errors:n})=>{const r=e.map((e=>new a.ScLinkContent(e.value,a.ScLinkContent.stringToType(e.type))));this.resolveOrReject(t,s,r,n)}))}))}))}searchLinksByContents(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((e=>({command:"find",data:e})));this.sendMessage("content",n,(({payload:e,errors:n})=>{const r=e.map((e=>e.map((e=>new c.ScAddr(e)))));this.resolveOrReject(t,s,r,n)}))}))}))}getLinksByContents(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `getLinksByContents` method is deprecated. Use `searchLinksByContents` instead."),this.searchLinksByContents(e)}))}searchLinksByContentSubstrings(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((e=>({command:"find_links_by_substr",data:e})));this.sendMessage("content",n,(({payload:e,errors:n})=>{const r=e.map((e=>e.map((e=>new c.ScAddr(e)))));this.resolveOrReject(t,s,r,n)}))}))}))}getLinksByContentSubstrings(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `getLinksByContentSubstrings` method is deprecated. Use `searchLinksByContentSubstrings` instead."),this.searchLinksByContentSubstrings(e)}))}searchLinkContentsByContentSubstrings(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((e=>({command:"find_strings_by_substr",data:e})));this.sendMessage("content",n,(({payload:e,errors:n})=>{this.resolveOrReject(t,s,e,n)}))}))}))}getLinksContentsByContentSubstrings(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `getLinksContentsByContentSubstrings` method is deprecated. Use `searchLinkContentsByContentSubstrings` instead."),this.searchLinkContentsByContentSubstrings(e)}))}resolveKeynodes(e){return n(this,void 0,void 0,(function*(){return new Promise(((t,s)=>{const n=e.map((({id:e,type:t})=>t.isValid()?{command:"resolve",idtf:e,elType:t.value}:{command:"find",idtf:e}));this.sendMessage("keynodes",n,(({payload:n,errors:r})=>{const o=n.map((e=>new c.ScAddr(e))).reduce(((t,s,n)=>Object.assign(Object.assign({},t),{[e[n].id]:s})),{});this.resolveOrReject(t,s,o,r)}))}))}))}processTripleItem({value:e,alias:t}){const s=t?{alias:t}:{};return e instanceof c.ScAddr?Object.assign({type:"addr",value:e.value},s):e instanceof _.ScType?Object.assign({type:"type",value:e.value},s):Object.assign({type:"alias",value:e},s)}processTemplate(e){return e instanceof c.ScAddr?{type:"addr",value:e.value}:"string"==typeof e&&/^[a-z0-9_]+$/.test(e)?{type:"idtf",value:e}:"string"==typeof e?e:e.triples.map((({source:e,connector:t,target:s})=>[this.processTripleItem(e),this.processTripleItem(t),this.processTripleItem(s)]))}processTemplateParams(e){return Object.keys(e).reduce(((t,s)=>{const n=e[s];return t[s]="string"==typeof n?n:n.value,t}),{})}searchByTemplate(e,t={}){return n(this,void 0,void 0,(function*(){return new Promise(((s,r)=>n(this,void 0,void 0,(function*(){const n={templ:this.processTemplate(e),params:this.processTemplateParams(t)};this.sendMessage("search_template",n,(({payload:e,status:t,errors:n})=>{if(!t)return s([]);const o=e.addrs.map((t=>{const s=t.map((e=>new c.ScAddr(e)));return new i.ScTemplateResult(e.aliases,s)}));this.resolveOrReject(s,r,o,n)}))}))))}))}templateSearch(e,t={}){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `templateSearch` method is deprecated. Use `searchByTemplate` instead."),this.searchByTemplate(e,t)}))}generateByTemplate(e,t={}){return n(this,void 0,void 0,(function*(){return new Promise(((s,r)=>n(this,void 0,void 0,(function*(){const n={templ:this.processTemplate(e),params:this.processTemplateParams(t)};this.sendMessage("generate_template",n,(({status:e,payload:t,errors:n})=>{e||s(null);const o=t.addrs.map((e=>new c.ScAddr(e))),a=new i.ScTemplateResult(t.aliases,o);this.resolveOrReject(s,r,a,n)}))}))))}))}templateGenerate(e,t={}){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `templateGenerate` method is deprecated. Use `generateByTemplate` instead."),this.generateByTemplate(e,t)}))}createElementaryEventSubscriptions(e){return n(this,void 0,void 0,(function*(){const t=Array.isArray(e)?e:[e];return new Promise(((e,s)=>{const n={create:t.map((({type:e,addr:t})=>({type:e,addr:t.value})))};this.sendMessage("events",n,(({payload:n,errors:r})=>{const c=t.map((({callback:e,type:t},s)=>{const r=n[s],c=new o.ScEventSubscription(r,t,e);return this._events[r]=c,c}));this.resolveOrReject(e,s,c,r)}))}))}))}eventsCreate(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `eventsCreate` method is deprecated. Use `createElementaryEventSubscriptions` instead."),this.createElementaryEventSubscriptions(e)}))}destroyElementaryEventSubscriptions(e){return n(this,void 0,void 0,(function*(){const t=Array.isArray(e)?e:[e];return new Promise(((e,s)=>{const n={delete:t};this.sendMessage("events",n,(({status:n,errors:r})=>{t.forEach((e=>{delete this._events[e]})),this.resolveOrReject(e,s,n,r)}))}))}))}eventsDestroy(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `eventsDestroy` method is deprecated. Use `destroyElementaryEventSubscriptions` instead."),this.destroyElementaryEventSubscriptions(e)}))}searchKeynodes(...e){return n(this,void 0,void 0,(function*(){const t=e.filter((e=>!this._keynodesCache.get(e))).map((e=>({id:e,type:_.ScType.ConstNode}))),s=e.filter((e=>this._keynodesCache.get(e))),n=this._keynodesCache.size+t.length-this._keynodesCacheSize;n>0&&(0,p.shiftMap)(this._keynodesCache,n);const r=t.length?yield this.resolveKeynodes(t):[],c=Object.entries(r),o=s.map((e=>[e,this._keynodesCache.get(e)]));c.forEach((([e,t])=>this._keynodesCache.set(e,t)));const a=[...c,...o].map((([e,t])=>[(0,p.snakeToCamelCase)(e),t]));return Object.fromEntries(a)}))}findKeynodes(...e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScClient `findKeynodes` method is deprecated. Use `searchKeynodes` instead."),this.searchKeynodes(...e)}))}}},(e,t)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.invalidValue=void 0,t.invalidValue=e=>{((e,t)=>{throw`Invalid value: : ${t}`})(0,e)}},(e,t)=>{var s;Object.defineProperty(t,"__esModule",{value:!0}),t.ScEventSubscription=t.ScEventType=void 0,(s=t.ScEventType||(t.ScEventType={})).Unknown="unknown",s.AfterGenerateConnector="sc_event_after_generate_connector",s.AfterGenerateOutgoingArc="sc_event_after_generate_outgoing_arc",s.AfterGenerateIncomingArc="sc_event_after_generate_incoming_arc",s.AfterGenerateEdge="sc_event_after_generate_edge",s.BeforeEraseConnector="sc_event_before_erase_connector",s.BeforeEraseOutgoingArc="sc_event_before_erase_outgoing_arc",s.BeforeEraseIncomingArc="sc_event_before_erase_incoming_arc",s.BeforeEraseEdge="sc_event_before_erase_edge",s.BeforeEraseElement="sc_event_before_erase_element",s.BeforeChangeLinkContent="sc_event_before_change_link_content",t.ScEventSubscription=class{constructor(e,t,s){this._id=0,this._type=null,this._callback=null,this._id=e,this._type=t,this._callback=s}get id(){return this._id}get type(){return this._type}get callback(){return this._callback}IsValid(){return this._id>0}}},(e,t)=>{var s;Object.defineProperty(t,"__esModule",{value:!0}),t.ScLinkContent=t.ScLinkContentType=void 0,function(e){e[e.Int=0]="Int",e[e.Float=1]="Float",e[e.String=2]="String",e[e.Binary=3]="Binary"}(s=t.ScLinkContentType||(t.ScLinkContentType={})),t.ScLinkContent=class{constructor(e,t,s){this._data=e,this._type=t,this._addr=s}get data(){return this._data}get type(){return this._type}get addr(){return this._addr}typeToStr(){switch(this._type){case s.Binary:return"binary";case s.Float:return"float";case s.Int:return"int";default:return"string"}}static stringToType(e){switch(e){case"binary":return s.Binary;case"float":return s.Float;case"int":return s.Int;default:return s.String}}}},(e,t)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.ScTemplateResult=void 0,t.ScTemplateResult=class{constructor(e,t){this._addrs=[],this._indecies={},this._indecies=e,this._addrs=t}get size(){return this._addrs.length}get(e){return"string"==typeof e?this._addrs[this._indecies[e]]:this._addrs[e]}forEachTriple(e){for(let t=0;t<this.size;t+=3)e(this._addrs[t],this._addrs[t+1],this._addrs[t+2])}}},(e,t,s)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.ScType=void 0;const n=s(8);class r{constructor(e){this._value="number"==typeof e?e||0:e instanceof r&&e._value||0}get value(){return this._value}hasConstancy(){return 0!=(this._value&n.sc_type_constancy_mask)}hasSubtype(e){return(this._value&e)==e}isConst(){return this.hasSubtype(n.sc_type_const)}isVar(){return this.hasSubtype(n.sc_type_var)}hasDirection(){return this.isArc()}isNode(){return this.hasSubtype(n.sc_type_node)}isLink(){return this.hasSubtype(n.sc_type_node_link)}isConnector(){return this.hasSubtype(n.sc_type_connector)}isEdge(){return console.warn("Warning: ScType `isEdge` method is deprecated. Use `isConnector` instead."),this.isConnector()}isCommonEdge(){return this.hasSubtype(n.sc_type_common_edge)}isArc(){return this.hasSubtype(n.sc_type_arc)}isCommonArc(){return this.hasSubtype(n.sc_type_common_arc)}isMembershipArc(){return this.hasSubtype(n.sc_type_membership_arc)}isPos(){return this.hasSubtype(n.sc_type_pos_arc)}isNeg(){return this.hasSubtype(n.sc_type_neg_arc)}isFuz(){return this.hasSubtype(n.sc_type_fuz_arc)}isPerm(){return this.hasSubtype(n.sc_type_perm_arc)}isTemp(){return this.hasSubtype(n.sc_type_temp_arc)}isActual(){return this.hasSubtype(n.sc_type_actual_arc)}isInactual(){return this.hasSubtype(n.sc_type_inactual_arc)}isTuple(){return this.hasSubtype(n.sc_type_node_tuple)}isStructure(){return this.hasSubtype(n.sc_type_node_structure)}isStruct(){return console.warn("Warning: ScType `isStruct` method is deprecated. Use `isStructure` instead."),this.isStructure()}isRole(){return this.hasSubtype(n.sc_type_node_role)}isNonRole(){return this.hasSubtype(n.sc_type_node_non_role)}isClass(){return this.hasSubtype(n.sc_type_node_class)}isSuperclass(){return this.hasSubtype(n.sc_type_node_superclass)}isMaterial(){return this.hasSubtype(n.sc_type_node_material)}isValid(){return 0!==this._value}equal(e){return this._value===e._value}static isNotCompatibleByMask(e,t,s){const r=e&s,c=t&s;return r!=n.sc_type_unknown&&r!=c}isExtendableTo(e){let t=this.value,s=e.value;if(r.isNotCompatibleByMask(t,s,n.sc_type_element_mask))return!1;if(r.isNotCompatibleByMask(t,s,n.sc_type_constancy_mask))return!1;if(this.isLink()){if(!e.isLink())return!1;if(new r(t&~n.sc_type_node_link),e=new r(s&~n.sc_type_node_link),r.isNotCompatibleByMask(t,s,n.sc_type_node_link_mask))return!1}else if(this.isNode()){if(!e.isNode())return!1;if(new r(t&~n.sc_type_node),e=new r(s&~n.sc_type_node),r.isNotCompatibleByMask(t,s,n.sc_type_node_mask))return!1}else if(this.isConnector()){if(e.isConnector())return!1;if(r.isNotCompatibleByMask(t,s,n.sc_type_connector_mask))if(this.isCommonEdge()){if(!e.isCommonEdge())return!1}else if(this.isArc()){if(!e.isArc())return!1;if(this.isCommonArc()){if(!e.isCommonArc())return!1}else if(!this.isMembershipArc()&&!e.isMembershipArc())return!1}if(new r(t&~n.sc_type_connector_mask),e=new r(s&~n.sc_type_connector_mask),r.isNotCompatibleByMask(t,s,n.sc_type_actuality_mask))return!1;if(r.isNotCompatibleByMask(t,s,n.sc_type_permanency_mask))return!1;if(r.isNotCompatibleByMask(t,s,n.sc_type_positivity_mask))return!1;if(r.isNotCompatibleByMask(t,s,n.sc_type_fuz_arc))return!1}return!0}merge(e){if(!this.isExtendableTo(e))throw"Type `"+this+"` can not be extended to `"+e+"`";return new r(this._value|e._value)}changeConst(e){const t=this._value&~n.sc_type_constancy_mask;return new r(t|(e?n.sc_type_const:n.sc_type_var))}}t.ScType=r,r.Unknown=new r(n.sc_type_unknown),r.Node=new r(n.sc_type_node),r.Connector=new r(n.sc_type_connector),r.CommonEdge=new r(n.sc_type_common_edge),r.Arc=new r(n.sc_type_arc),r.CommonArc=new r(n.sc_type_common_arc),r.MembershipArc=new r(n.sc_type_membership_arc),r.Const=new r(n.sc_type_const),r.Var=new r(n.sc_type_var),r.ConstNode=new r(n.sc_type_const|n.sc_type_node),r.VarNode=new r(n.sc_type_var|n.sc_type_node),r.ConstConnector=new r(n.sc_type_const|n.sc_type_connector),r.VarConnector=new r(n.sc_type_var|n.sc_type_connector),r.ConstCommonEdge=new r(n.sc_type_const|n.sc_type_common_edge),r.VarCommonEdge=new r(n.sc_type_var|n.sc_type_common_edge),r.ConstArc=new r(n.sc_type_const|n.sc_type_arc),r.VarArc=new r(n.sc_type_var|n.sc_type_arc),r.ConstCommonArc=new r(n.sc_type_const|n.sc_type_common_arc),r.VarCommonArc=new r(n.sc_type_var|n.sc_type_common_arc),r.ConstMembershipArc=new r(n.sc_type_const|n.sc_type_membership_arc),r.VarMembershipArc=new r(n.sc_type_var|n.sc_type_membership_arc),r.PermArc=new r(n.sc_type_perm_arc),r.TempArc=new r(n.sc_type_temp_arc),r.ConstPermArc=new r(n.sc_type_const|n.sc_type_perm_arc),r.VarPermArc=new r(n.sc_type_var|n.sc_type_perm_arc),r.ConstTempArc=new r(n.sc_type_const|n.sc_type_temp_arc),r.VarTempArc=new r(n.sc_type_var|n.sc_type_temp_arc),r.ActualTempArc=new r(n.sc_type_actual_arc|n.sc_type_temp_arc),r.InactualTempArc=new r(n.sc_type_inactual_arc|n.sc_type_temp_arc),r.ConstActualTempArc=new r(n.sc_type_const|n.sc_type_actual_arc|n.sc_type_temp_arc),r.VarActualTempArc=new r(n.sc_type_var|n.sc_type_actual_arc|n.sc_type_temp_arc),r.ConstInactualTempArc=new r(n.sc_type_const|n.sc_type_inactual_arc|n.sc_type_temp_arc),r.VarInactualTempArc=new r(n.sc_type_var|n.sc_type_inactual_arc|n.sc_type_temp_arc),r.PosArc=new r(n.sc_type_pos_arc),r.NegArc=new r(n.sc_type_neg_arc),r.ConstPosArc=new r(n.sc_type_const|n.sc_type_pos_arc),r.VarPosArc=new r(n.sc_type_var|n.sc_type_pos_arc),r.PermPosArc=new r(n.sc_type_perm_arc|n.sc_type_pos_arc),r.TempPosArc=new r(n.sc_type_temp_arc|n.sc_type_pos_arc),r.ActualTempPosArc=new r(n.sc_type_actual_arc|n.sc_type_temp_arc|n.sc_type_pos_arc),r.InactualTempPosArc=new r(n.sc_type_inactual_arc|n.sc_type_temp_arc|n.sc_type_pos_arc),r.ConstPermPosArc=new r(n.sc_type_const|n.sc_type_perm_arc|n.sc_type_pos_arc),r.ConstTempPosArc=new r(n.sc_type_const|n.sc_type_temp_arc|n.sc_type_pos_arc),r.ConstActualTempPosArc=new r(n.sc_type_const|n.sc_type_actual_arc|n.sc_type_temp_arc|n.sc_type_pos_arc),r.ConstInactualTempPosArc=new r(n.sc_type_const|n.sc_type_inactual_arc|n.sc_type_temp_arc|n.sc_type_pos_arc),r.VarPermPosArc=new r(n.sc_type_var|n.sc_type_perm_arc|n.sc_type_pos_arc),r.VarTempPosArc=new r(n.sc_type_var|n.sc_type_temp_arc|n.sc_type_pos_arc),r.VarActualTempPosArc=new r(n.sc_type_var|n.sc_type_actual_arc|n.sc_type_temp_arc|n.sc_type_pos_arc),r.VarInactualTempPosArc=new r(n.sc_type_var|n.sc_type_inactual_arc|n.sc_type_temp_arc|n.sc_type_pos_arc),r.ConstNegArc=new r(n.sc_type_const|n.sc_type_neg_arc),r.VarNegArc=new r(n.sc_type_var|n.sc_type_neg_arc),r.PermNegArc=new r(n.sc_type_perm_arc|n.sc_type_neg_arc),r.TempNegArc=new r(n.sc_type_temp_arc|n.sc_type_neg_arc),r.ActualTempNegArc=new r(n.sc_type_actual_arc|n.sc_type_temp_arc|n.sc_type_neg_arc),r.InactualTempNegArc=new r(n.sc_type_inactual_arc|n.sc_type_temp_arc|n.sc_type_neg_arc),r.ConstPermNegArc=new r(n.sc_type_const|n.sc_type_perm_arc|n.sc_type_neg_arc),r.ConstTempNegArc=new r(n.sc_type_const|n.sc_type_temp_arc|n.sc_type_neg_arc),r.ConstActualTempNegArc=new r(n.sc_type_const|n.sc_type_actual_arc|n.sc_type_temp_arc|n.sc_type_neg_arc),r.ConstInactualTempNegArc=new r(n.sc_type_const|n.sc_type_inactual_arc|n.sc_type_temp_arc|n.sc_type_neg_arc),r.VarPermNegArc=new r(n.sc_type_var|n.sc_type_perm_arc|n.sc_type_neg_arc),r.VarTempNegArc=new r(n.sc_type_var|n.sc_type_temp_arc|n.sc_type_neg_arc),r.VarActualTempNegArc=new r(n.sc_type_var|n.sc_type_actual_arc|n.sc_type_temp_arc|n.sc_type_neg_arc),r.VarInactualTempNegArc=new r(n.sc_type_var|n.sc_type_inactual_arc|n.sc_type_temp_arc|n.sc_type_neg_arc),r.FuzArc=new r(n.sc_type_fuz_arc),r.ConstFuzArc=new r(n.sc_type_const|n.sc_type_fuz_arc),r.VarFuzArc=new r(n.sc_type_var|n.sc_type_fuz_arc),r.NodeLink=new r(n.sc_type_node_link),r.NodeLinkClass=new r(n.sc_type_node_link|n.sc_type_node_class),r.NodeTuple=new r(n.sc_type_node_tuple),r.NodeStructure=new r(n.sc_type_node_structure),r.NodeRole=new r(n.sc_type_node_role),r.NodeNonRole=new r(n.sc_type_node_non_role),r.NodeClass=new r(n.sc_type_node_class),r.NodeSuperclass=new r(n.sc_type_node_superclass),r.NodeMaterial=new r(n.sc_type_node_material),r.ConstNodeLink=new r(n.sc_type_const|n.sc_type_node_link),r.ConstNodeLinkClass=new r(n.sc_type_const|n.sc_type_node_link|n.sc_type_node_class),r.ConstNodeTuple=new r(n.sc_type_const|n.sc_type_node_tuple),r.ConstNodeStructure=new r(n.sc_type_const|n.sc_type_node_structure),r.ConstNodeRole=new r(n.sc_type_const|n.sc_type_node_role),r.ConstNodeNonRole=new r(n.sc_type_const|n.sc_type_node_non_role),r.ConstNodeClass=new r(n.sc_type_const|n.sc_type_node_class),r.ConstNodeSuperclass=new r(n.sc_type_const|n.sc_type_node_superclass),r.ConstNodeMaterial=new r(n.sc_type_const|n.sc_type_node_material),r.VarNodeLink=new r(n.sc_type_var|n.sc_type_node_link),r.VarNodeLinkClass=new r(n.sc_type_var|n.sc_type_node_link|n.sc_type_node_class),r.VarNodeTuple=new r(n.sc_type_var|n.sc_type_node_tuple),r.VarNodeStructure=new r(n.sc_type_var|n.sc_type_node_structure),r.VarNodeRole=new r(n.sc_type_var|n.sc_type_node_role),r.VarNodeNonRole=new r(n.sc_type_var|n.sc_type_node_non_role),r.VarNodeClass=new r(n.sc_type_var|n.sc_type_node_class),r.VarNodeSuperclass=new r(n.sc_type_var|n.sc_type_node_superclass),r.VarNodeMaterial=new r(n.sc_type_var|n.sc_type_node_material),r.EdgeUCommon=new r(r.CommonEdge),r.EdgeDCommon=new r(r.CommonArc),r.EdgeUCommonConst=new r(r.ConstCommonEdge),r.EdgeDCommonConst=new r(r.ConstCommonArc),r.EdgeAccess=new r(r.MembershipArc),r.EdgeAccessConstPosPerm=new r(r.ConstPermPosArc),r.EdgeAccessConstNegPerm=new r(r.ConstPermNegArc),r.EdgeAccessConstFuzPerm=new r(r.ConstFuzArc),r.EdgeAccessConstPosTemp=new r(r.ConstTempPosArc),r.EdgeAccessConstNegTemp=new r(r.ConstTempNegArc),r.EdgeAccessConstFuzTemp=new r(r.ConstFuzArc),r.EdgeUCommonVar=new r(r.VarCommonEdge),r.EdgeDCommonVar=new r(r.VarCommonArc),r.EdgeAccessVarPosPerm=new r(r.VarPermPosArc),r.EdgeAccessVarNegPerm=new r(r.VarPermNegArc),r.EdgeAccessVarFuzPerm=new r(r.VarFuzArc),r.EdgeAccessVarPosTemp=new r(r.VarTempPosArc),r.EdgeAccessVarNegTemp=new r(r.VarTempNegArc),r.EdgeAccessVarFuzTemp=new r(r.VarFuzArc),r.NodeConst=new r(r.ConstNode),r.NodeVar=new r(r.VarNode),r.Link=new r(r.NodeLink),r.LinkClass=new r(r.NodeLinkClass),r.NodeStruct=new r(r.NodeStructure),r.LinkConst=new r(r.ConstNodeLink),r.LinkConstClass=new r(r.ConstNodeLinkClass),r.NodeConstTuple=new r(r.ConstNodeTuple),r.NodeConstStruct=new r(r.ConstNodeStructure),r.NodeConstRole=new r(r.ConstNodeRole),r.NodeConstNoRole=new r(r.ConstNodeNonRole),r.NodeConstClass=new r(r.ConstNodeClass),r.NodeConstMaterial=new r(r.ConstNodeMaterial),r.LinkVar=new r(r.VarNodeLink),r.LinkVarClass=new r(r.VarNodeLinkClass),r.NodeVarStruct=new r(r.VarNodeStructure),r.NodeVarTuple=new r(r.VarNodeTuple),r.NodeVarRole=new r(r.VarNodeRole),r.NodeVarNoRole=new r(r.VarNodeNonRole),r.NodeVarClass=new r(r.VarNodeClass),r.NodeVarMaterial=new r(r.VarNodeMaterial)},(e,t)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.DEFAULT_KEYNODES_CACHE_SIZE=t.sc_type_node_link_mask=t.sc_type_node_mask=t.sc_type_common_edge_mask=t.sc_type_common_arc_mask=t.sc_type_membership_arc_mask=t.sc_type_positivity_mask=t.sc_type_permanency_mask=t.sc_type_actuality_mask=t.sc_type_constancy_mask=t.sc_type_arc_mask=t.sc_type_connector_mask=t.sc_type_element_mask=t.sc_type_node_material=t.sc_type_node_superclass=t.sc_type_node_class=t.sc_type_node_non_role=t.sc_type_node_role=t.sc_type_node_structure=t.sc_type_node_tuple=t.sc_type_node_link=t.sc_type_fuz_arc=t.sc_type_neg_arc=t.sc_type_pos_arc=t.sc_type_perm_arc=t.sc_type_temp_arc=t.sc_type_inactual_arc=t.sc_type_actual_arc=t.sc_type_var=t.sc_type_const=t.sc_type_membership_arc=t.sc_type_common_arc=t.sc_type_arc=t.sc_type_common_edge=t.sc_type_connector=t.sc_type_node=t.sc_type_unknown=void 0,t.sc_type_unknown=0,t.sc_type_node=1,t.sc_type_connector=16384,t.sc_type_common_edge=4|t.sc_type_connector,t.sc_type_arc=32768|t.sc_type_connector,t.sc_type_common_arc=8|t.sc_type_arc,t.sc_type_membership_arc=16|t.sc_type_arc,t.sc_type_const=32,t.sc_type_var=64,t.sc_type_actual_arc=4096|t.sc_type_membership_arc,t.sc_type_inactual_arc=8192|t.sc_type_membership_arc,t.sc_type_temp_arc=1024|t.sc_type_membership_arc,t.sc_type_perm_arc=2048|t.sc_type_membership_arc,t.sc_type_pos_arc=128|t.sc_type_membership_arc,t.sc_type_neg_arc=256|t.sc_type_membership_arc,t.sc_type_fuz_arc=512|t.sc_type_membership_arc,t.sc_type_node_link=2|t.sc_type_node,t.sc_type_node_tuple=128|t.sc_type_node,t.sc_type_node_structure=256|t.sc_type_node,t.sc_type_node_role=512|t.sc_type_node,t.sc_type_node_non_role=1024|t.sc_type_node,t.sc_type_node_class=2048|t.sc_type_node,t.sc_type_node_superclass=4096|t.sc_type_node,t.sc_type_node_material=8192|t.sc_type_node,t.sc_type_element_mask=t.sc_type_node|t.sc_type_connector,t.sc_type_connector_mask=t.sc_type_common_edge|t.sc_type_common_arc|t.sc_type_membership_arc,t.sc_type_arc_mask=t.sc_type_common_arc|t.sc_type_membership_arc,t.sc_type_constancy_mask=t.sc_type_const|t.sc_type_var,t.sc_type_actuality_mask=t.sc_type_actual_arc|t.sc_type_inactual_arc,t.sc_type_permanency_mask=t.sc_type_perm_arc|t.sc_type_temp_arc,t.sc_type_positivity_mask=t.sc_type_pos_arc|t.sc_type_neg_arc,t.sc_type_membership_arc_mask=t.sc_type_actuality_mask|t.sc_type_permanency_mask|t.sc_type_positivity_mask|t.sc_type_fuz_arc,t.sc_type_common_arc_mask=t.sc_type_common_arc,t.sc_type_common_edge_mask=t.sc_type_common_edge,t.sc_type_node_mask=t.sc_type_node_link|t.sc_type_node_tuple|t.sc_type_node_structure|t.sc_type_node_role|t.sc_type_node_non_role|t.sc_type_node_class|t.sc_type_node_superclass|t.sc_type_node_material,t.sc_type_node_link_mask=t.sc_type_node|t.sc_type_node_link|t.sc_type_node_class,t.DEFAULT_KEYNODES_CACHE_SIZE=5e3},(e,t,s)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.snakeToCamelCase=t.shiftMap=t.transformConnectorInfo=void 0;const n=s(3);t.transformConnectorInfo=(e,t)=>{if("string"!=typeof t)return{type:"addr",value:t.value};const s=e.getIndex(t);return void 0===s?(0,n.invalidValue)(`Invalid alias: ${s}`):{type:"ref",value:s}},t.shiftMap=(e,t=1)=>{if(t<1)return;let s=!1,n=0;const r=e.keys();for(;n<t&&!s;){const t=r.next();s=!!t.done,e.delete(t.value),n++}},t.snakeToCamelCase=e=>e.replace(/_(\w)/g,((e,t)=>t.toUpperCase()))},(e,t,s)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.ScConstruction=void 0;const n=s(3),r=s(11);t.ScConstruction=class{constructor(){this._commands=[],this._aliases={}}generateNode(e,t){e.isNode()||(0,n.invalidValue)("You should pass node type there");const s=new r.ScConstructionCommand(e);t&&(this._aliases[t]=this._commands.length),this._commands.push(s)}createNode(e,t){console.warn("Warning: ScConstruction `createNode` method is deprecated. Use `generateNode` instead."),this.generateNode(e,t)}generateConnector(e,t,s,c){e.isConnector()||(0,n.invalidValue)("You should pass connector type there");const o=new r.ScConstructionCommand(e,{src:t,trg:s});c&&(this._aliases[c]=this._commands.length),this._commands.push(o)}createEdge(e,t,s,n){console.warn("Warning: ScConstruction `createEdge` method is deprecated. Use `generateConnector` instead."),this.generateConnector(e,t,s,n)}generateLink(e,t,s){e.isLink()||(0,n.invalidValue)("You should pass link type there");const c=new r.ScConstructionCommand(e,{content:t.data,type:t.type});s&&(this._aliases[s]=this._commands.length),this._commands.push(c)}createLink(e,t,s){console.warn("Warning: ScConstruction `createLink` method is deprecated. Use `generateLink` instead."),this.generateLink(e,t,s)}get commands(){return this._commands}getIndex(e){return this._aliases[e]}}},(e,t)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.ScConstructionCommand=void 0,t.ScConstructionCommand=class{constructor(e,t){this._elType=e,this._data=t}get type(){return this._elType}get data(){return this._data}}},(e,t)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.ScEventSubscriptionParams=void 0,t.ScEventSubscriptionParams=class{constructor(e,t,s){this._addr=e,this._type=t,this._callback=s}get addr(){return this._addr}get type(){return this._type}get callback(){return this._callback}}},function(e,t,s){var n=this&&this.__awaiter||function(e,t,s,n){return new(s||(s=Promise))((function(r,c){function o(e){try{i(n.next(e))}catch(e){c(e)}}function a(e){try{i(n.throw(e))}catch(e){c(e)}}function i(e){var t;e.done?r(e.value):(t=e.value,t instanceof s?t:new s((function(e){e(t)}))).then(o,a)}i((n=n.apply(e,t||[])).next())}))};Object.defineProperty(t,"__esModule",{value:!0}),t.ScSet=void 0;const r=s(4),c=s(12),o=s(14),a=s(7);t.ScSet=class{constructor(e,t,s,n,r,c){if(this._elements={},this._scClient=null,this._addr=null,this._onAdd=null,this._onRemove=null,this._onInitialize=null,this._filterType=null,this._scClient=e,this._addr=t,this._onInitialize=s,this._onAdd=n,this._onRemove=r,this._filterType=c,!this._addr||!this._addr.isValid())throw`Invalid addr of set: ${this._addr}`}initialize(){var e;return n(this,void 0,void 0,(function*(){if(!this._addr)return;const t=yield null===(e=this._scClient)||void 0===e?void 0:e.createElementaryEventSubscriptions([new c.ScEventSubscriptionParams(this._addr,r.ScEventType.AfterGenerateOutgoingArc,this.onEventGenerateElement.bind(this)),new c.ScEventSubscriptionParams(this._addr,r.ScEventType.BeforeEraseOutgoingArc,this.onEventEraseElement.bind(this))]);return this._evtGenerateElement=null==t?void 0:t[0],this._evtEraseElement=null==t?void 0:t[1],yield this.iterateExistingElements(),new Promise((function(e){e()}))}))}shouldAppend(e){var t;return n(this,void 0,void 0,(function*(){const s=yield null===(t=this._scClient)||void 0===t?void 0:t.getElementsTypes(e),n=null==s?void 0:s.map((e=>!(this._filterType&&(this._filterType.value&e.value)!==this._filterType.value)));return new Promise((function(e){e(n)}))}))}onEventGenerateElement(e,t,s){return n(this,void 0,void 0,(function*(){if(!this._elements[t.value]&&s.isValid()){const e=yield this.shouldAppend([s]);(null==e?void 0:e[0])&&(this._elements[t.value]=s,this.callOnAdd(s))}return new Promise((function(e){e()}))}))}onEventEraseElement(e,t){return n(this,void 0,void 0,(function*(){const e=this._elements[t.value];if(!e)throw`Invalid state of set: ${this._addr} (try to remove element ${t}, that doesn't exist)`;return yield this.callOnRemove(e),delete this._elements[t.value],new Promise((function(e){e()}))}))}callOnInitialize(e){return n(this,void 0,void 0,(function*(){return this._onInitialize&&(yield this._onInitialize(e)),new Promise((function(e){e()}))}))}callOnAdd(e){return n(this,void 0,void 0,(function*(){return this._onAdd&&(yield this._onAdd(e)),new Promise((function(e){e()}))}))}callOnRemove(e){return n(this,void 0,void 0,(function*(){return this._onRemove&&(yield this._onRemove(e)),new Promise((function(e){e()}))}))}iterateExistingElements(){return n(this,void 0,void 0,(function*(){if(!this._addr||!this._scClient)return;const e=[],t=new o.ScTemplate;t.triple(this._addr,[a.ScType.VarPermPosArc,"_arc"],[a.ScType.Unknown,"_item"]);const s=yield this._scClient.searchByTemplate(t),n=(null==s?void 0:s.map((e=>e.get("_item"))))||[],r=yield this.shouldAppend(n);for(let t=0;t<s.length;++t){if(!(null==r?void 0:r[t]))continue;const n=s[t].get("_arc"),c=s[t].get("_item");if(this._elements[n.value])throw`Element ${c} already exist in set`;this._elements[n.value]=c,e.push(c)}return yield this.callOnInitialize(e),new Promise((function(e){e()}))}))}addItem(e){return n(this,void 0,void 0,(function*(){if(!this._addr||!this._scClient)return;let t=!1;const s=new o.ScTemplate;if(s.triple(this._addr,[a.ScType.VarPermPosArc,"_arc"],[e,"_item"]),0==(yield this._scClient.searchByTemplate(s)).length){const n=yield this._scClient.generateByTemplate(s,{_item:e});if(n){const e=n.get("_item");t=e&&e.isValid()}}return new Promise((function(e){e(t)}))}))}}},(e,t,s)=>{Object.defineProperty(t,"__esModule",{value:!0}),t.ScTemplate=void 0;const n=s(1),r=s(7);t.ScTemplate=class{constructor(){this._triples=[]}get triples(){return this._triples}triple(e,t,s){const n=this.splitTemplateParam(e),r=this.splitTemplateParam(t),c=this.splitTemplateParam(s);return this._triples.push({source:n,connector:r,target:c}),this}quintuple(e,t,s,n,r){let{alias:c,value:o}=this.splitTemplateParam(t);return c||(c=`connector_1_${this._triples.length}`),this.triple(e,[o,c],s),this.triple(r,n,c),this}tripleWithRelation(e,t,s,n,r){return console.warn("Warning: ScTemplate `tripleWithRelation` method is deprecated. Use `quintuple` instead."),this.quintuple(e,t,s,n,r)}splitTemplateParam(e){if(e instanceof Array){if(2!==e.length)throw"Invalid number of values for replacement. Use [ScType | ScAddr, string]";const t=e[0],s=e[1];if(!(t instanceof n.ScAddr||t instanceof r.ScType)||"string"!=typeof s)throw"First parameter should be ScAddr or ScType. The second one - string";return{alias:s,value:t}}return{alias:null,value:e}}}},function(e,t,s){var n=this&&this.__awaiter||function(e,t,s,n){return new(s||(s=Promise))((function(r,c){function o(e){try{i(n.next(e))}catch(e){c(e)}}function a(e){try{i(n.throw(e))}catch(e){c(e)}}function i(e){var t;e.done?r(e.value):(t=e.value,t instanceof s?t:new s((function(e){e(t)}))).then(o,a)}i((n=n.apply(e,t||[])).next())}))},r=this&&this.__rest||function(e,t){var s={};for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&t.indexOf(n)<0&&(s[n]=e[n]);if(null!=e&&"function"==typeof Object.getOwnPropertySymbols){var r=0;for(n=Object.getOwnPropertySymbols(e);r<n.length;r++)t.indexOf(n[r])<0&&Object.prototype.propertyIsEnumerable.call(e,n[r])&&(s[n[r]]=e[n[r]])}return s};Object.defineProperty(t,"__esModule",{value:!0}),t.ScHelper=void 0;const c=s(10),o=s(4),a=s(12),i=s(5),_=s(14),p=s(7),d=s(9);t.ScHelper=class{constructor(e){this._client=e}getMainIdentifierLinkAddr(e,t){return n(this,void 0,void 0,(function*(){const s=yield this._client.searchKeynodes("nrel_main_idtf",t),{nrelMainIdtf:n}=s,c=r(s,["nrelMainIdtf"])[(0,d.snakeToCamelCase)(t)],o=new _.ScTemplate,a="_link";o.quintuple(e,p.ScType.VarCommonArc,[p.ScType.VarNodeLink,a],p.ScType.VarPermPosArc,n),o.triple(c,p.ScType.VarPermPosArc,a);const i=yield this._client.searchByTemplate(o);return i.length?i[0].get(a):null}))}getMainIdentifier(e,t){return n(this,void 0,void 0,(function*(){const s=yield this.getMainIdentifierLinkAddr(e,t);return s?(yield this._client.getLinkContents([s]))[0].data:null}))}getSystemIdentifier(e){return n(this,void 0,void 0,(function*(){const{nrelSystemIdentifier:t}=yield this._client.searchKeynodes("nrel_system_identifier"),s=new _.ScTemplate,n="_link";s.quintuple(e,p.ScType.VarCommonArc,[p.ScType.VarNodeLink,n],p.ScType.VarPermPosArc,t);const r=yield this._client.searchByTemplate(s);if(!r.length)return null;const c=yield this._client.getLinkContents([r[0].get(n)]);return String(c[0].data)}))}getScIdentifier(e,t){return n(this,void 0,void 0,(function*(){const s=yield this.getMainIdentifier(e,t);if(s)return String(s);const n=yield this.getSystemIdentifier(e);return String(n||e.value)}))}getAddrOrSystemIdentifierAddr(e){return n(this,void 0,void 0,(function*(){const t=Number(e);return t||(yield this._client.searchKeynodes(String(e)))[(0,d.snakeToCamelCase)(String(e))].value}))}getResult(e){return new Promise((t=>{(()=>{n(this,void 0,void 0,(function*(){var s;const{nrelResult:r}=yield this._client.searchKeynodes("nrel_result"),c=new a.ScEventSubscriptionParams(e,o.ScEventType.AfterGenerateOutgoingArc,((e,s,c,o)=>n(this,void 0,void 0,(function*(){const e=new _.ScTemplate;e.triple(r,p.ScType.VarPermPosArc,s),(yield this._client.searchByTemplate(e)).length&&(this._client.destroyElementaryEventSubscriptions(o),t(c))})))),[i]=yield this._client.createElementaryEventSubscriptions(c),d="_result",l=new _.ScTemplate;l.quintuple(e,p.ScType.VarCommonArc,[p.ScType.VarNode,d],p.ScType.VarPermPosArc,r);const u=null===(s=(yield this._client.searchByTemplate(l))[0])||void 0===s?void 0:s.get(d);u&&(this._client.destroyElementaryEventSubscriptions(i.id),t(u))}))})()}))}getAnswer(e){return console.warn("Warning: ScHelper `getAnswer` method is deprecated. Use `getResult` instead."),this.getResult(e)}generateLink(e){return n(this,void 0,void 0,(function*(){const t=new c.ScConstruction;t.generateLink(p.ScType.ConstNodeLink,new i.ScLinkContent(e,i.ScLinkContentType.String));const s=yield this._client.generateElements(t);return s.length?s[0]:null}))}createLink(e){return n(this,void 0,void 0,(function*(){return console.warn("Warning: ScHelper `createLink` method is deprecated. Use `generateLink` instead."),this.generateLink(e)}))}}}],t={};return function s(n){var r=t[n];if(void 0!==r)return r.exports;var c=t[n]={exports:{}};return e[n].call(c.exports,c,c.exports,s),c.exports}(0)})()));
// sc-element types
const sc_type_unknown = 0
const sc_type_node = 0x1
const sc_type_connector = 0x4000
const sc_type_common_edge = (sc_type_connector | 0x4)
const sc_type_arc = (sc_type_connector | 0x8000)
const sc_type_common_arc = (sc_type_arc | 0x8)
const sc_type_membership_arc = (sc_type_arc | 0x10)

// sc-element constant
const sc_type_const = 0x20
const sc_type_var = 0x40

// sc-arc actuality
const sc_type_actual_arc = (sc_type_membership_arc | 0x1000)
const sc_type_inactual_arc = (sc_type_membership_arc | 0x2000)

// sc-arc permanence
const sc_type_temp_arc = (sc_type_membership_arc | 0x400)
const sc_type_perm_arc = (sc_type_membership_arc | 0x800)

// sc-arc positivity
const sc_type_pos_arc = (sc_type_membership_arc | 0x80)
const sc_type_neg_arc = (sc_type_membership_arc | 0x100)

// fuzziness
const sc_type_fuz_arc = (sc_type_membership_arc | 0x200)

// semantic sc-node types
const sc_type_node_link = (sc_type_node | 0x2)
const sc_type_node_tuple = (sc_type_node | 0x80)
const sc_type_node_structure = (sc_type_node | 0x100)
const sc_type_node_role = (sc_type_node | 0x200)
const sc_type_node_non_role = (sc_type_node | 0x400)
const sc_type_node_class = (sc_type_node | 0x800)
const sc_type_node_superclass = (sc_type_node | 0x1000)
const sc_type_node_material = (sc_type_node | 0x2000)

const sc_type_const_pos_arc = (sc_type_const | sc_type_pos_arc)
const sc_type_const_neg_arc = (sc_type_const | sc_type_neg_arc)
const sc_type_const_fuz_arc = (sc_type_const | sc_type_fuz_arc)

const sc_type_const_perm_pos_arc = (sc_type_const | sc_type_perm_arc | sc_type_pos_arc)
const sc_type_const_perm_neg_arc = (sc_type_const | sc_type_perm_arc | sc_type_neg_arc)
const sc_type_const_temp_pos_arc = (sc_type_const | sc_type_temp_arc | sc_type_pos_arc)
const sc_type_const_temp_neg_arc = (sc_type_const | sc_type_temp_arc | sc_type_neg_arc)

const sc_type_const_actual_temp_pos_arc = (sc_type_const | sc_type_actual_arc | sc_type_temp_arc | sc_type_pos_arc)
const sc_type_const_actual_temp_neg_arc = (sc_type_const | sc_type_actual_arc | sc_type_temp_arc | sc_type_neg_arc)
const sc_type_const_inactual_temp_pos_arc = (sc_type_const | sc_type_inactual_arc | sc_type_temp_arc | sc_type_pos_arc)
const sc_type_const_inactual_temp_neg_arc = (sc_type_const | sc_type_inactual_arc | sc_type_temp_arc | sc_type_neg_arc)

const sc_type_var_perm_pos_arc = (sc_type_var | sc_type_perm_arc | sc_type_pos_arc)
const sc_type_var_perm_neg_arc = (sc_type_var | sc_type_perm_arc | sc_type_neg_arc)
const sc_type_var_temp_pos_arc = (sc_type_var | sc_type_temp_arc | sc_type_pos_arc)
const sc_type_var_temp_neg_arc = (sc_type_var | sc_type_temp_arc | sc_type_neg_arc)

const sc_type_var_actual_temp_pos_arc = (sc_type_var | sc_type_actual_arc | sc_type_temp_arc | sc_type_pos_arc)
const sc_type_var_actual_temp_neg_arc = (sc_type_var | sc_type_actual_arc | sc_type_temp_arc | sc_type_neg_arc)
const sc_type_var_inactual_temp_pos_arc = (sc_type_var | sc_type_inactual_arc | sc_type_temp_arc | sc_type_pos_arc)
const sc_type_var_inactual_temp_neg_arc = (sc_type_var | sc_type_inactual_arc | sc_type_temp_arc | sc_type_neg_arc)

const sc_type_var_fuz_arc = (sc_type_const | sc_type_fuz_arc)

const sc_type_const_common_arc = (sc_type_const | sc_type_common_arc)
const sc_type_var_common_arc = (sc_type_var | sc_type_common_arc)
const sc_type_const_common_edge = (sc_type_const | sc_type_common_edge)
const sc_type_var_common_edge = (sc_type_var | sc_type_common_edge)

const sc_type_const_node = (sc_type_const | sc_type_node)
const sc_type_const_node_link = (sc_type_const | sc_type_node | sc_type_node_link)
const sc_type_const_node_link_class = (sc_type_const | sc_type_node | sc_type_node_link | sc_type_node_class)
const sc_type_const_node_tuple = (sc_type_const | sc_type_node | sc_type_node_tuple)
const sc_type_const_node_structure = (sc_type_const | sc_type_node | sc_type_node_structure)
const sc_type_const_node_role = (sc_type_const | sc_type_node | sc_type_node_role)
const sc_type_const_node_non_role = (sc_type_const | sc_type_node | sc_type_node_non_role)
const sc_type_const_node_class = (sc_type_const | sc_type_node | sc_type_node_class)
const sc_type_const_node_superclass = (sc_type_const | sc_type_node | sc_type_node_superclass)
const sc_type_const_node_material = (sc_type_const | sc_type_node | sc_type_node_material)

const sc_type_var_node = (sc_type_var | sc_type_node)
const sc_type_var_node_link = (sc_type_var | sc_type_node | sc_type_node_link)
const sc_type_var_node_link_class = (sc_type_var | sc_type_node | sc_type_node_link | sc_type_node_class)
const sc_type_var_node_tuple = (sc_type_var | sc_type_node | sc_type_node_tuple)
const sc_type_var_node_structure = (sc_type_var | sc_type_node | sc_type_node_structure)
const sc_type_var_node_role = (sc_type_var | sc_type_node | sc_type_node_role)
const sc_type_var_node_non_role = (sc_type_var | sc_type_node | sc_type_node_non_role)
const sc_type_var_node_class = (sc_type_var | sc_type_node | sc_type_node_class)
const sc_type_var_node_superclass = (sc_type_var | sc_type_node | sc_type_node_superclass)
const sc_type_var_node_material = (sc_type_var | sc_type_node | sc_type_node_material)

// type mask
const sc_type_element_mask = (sc_type_node | sc_type_connector)
const sc_type_connector_mask = (sc_type_common_edge | sc_type_common_arc | sc_type_membership_arc)
const sc_type_arc_mask = (sc_type_common_arc | sc_type_membership_arc)

const sc_type_constancy_mask = (sc_type_const | sc_type_var)
const sc_type_actuality_mask = (sc_type_actual_arc | sc_type_inactual_arc)
const sc_type_permanency_mask = (sc_type_perm_arc | sc_type_temp_arc)
const sc_type_positivity_mask = (sc_type_pos_arc | sc_type_neg_arc)

const sc_type_membership_arc_mask = (sc_type_actuality_mask | sc_type_permanency_mask | sc_type_positivity_mask)
const sc_type_common_arc_mask = (sc_type_common_arc)
const sc_type_common_edge_mask = (sc_type_common_edge)

const sc_type_node_mask = (sc_type_node_link | sc_type_node_tuple | sc_type_node_structure | sc_type_node_role | sc_type_node_non_role
        | sc_type_node_class | sc_type_node_superclass | sc_type_node_material)
const sc_type_node_link_mask = (sc_type_node | sc_type_node_link | sc_type_node_class)

let ScKeynodes = function (helper) {
  this.helper = helper;
  this.scClient = helper.scClient;
};

ScKeynodes.prototype.init = async function () {
  await this.resolveKeynode([
    'nrel_system_identifier',
    'nrel_main_idtf',
    'nrel_idtf',
    'nrel_result',
    'basic_ontology_structure',

    'ui_user',
    'ui_user_registered',
    'ui_main_menu',
    'ui_user_command_class_atom',
    'ui_user_command_class_noatom',
    'ui_external_languages',
    'ui_rrel_command_arguments',
    'ui_rrel_command',
    'ui_nrel_command_result',
    'ui_nrel_user_answer_formats',

    'nrel_ui_commands_decomposition',

    'ui_expert_mode',
    'ui_menu_erase_elements',
    'ui_command_initiated',
    'ui_command_finished',
    'ui_nrel_user_used_language',
    'ui_nrel_user_default_ext_language',

    'languages',
    'lang_ru',
    'lang_en',

    'nrel_format',
    'nrel_mimetype',
    'format_txt',

    'binary_types',
    'binary_float',
    'binary_int8',
    'binary_int16',
    'binary_int32',
    'binary_int64',
    'format_pdf',
    'format_png',
    'format_html',
    'ui_start_sc_element',
    'rrel_key_sc_element',
    'rrel_main_key_sc_element',
  ]
  );
};

ScKeynodes.prototype.resolveKeynode = async function (sys_idtf, property) {
  if (property) {
    throw new Error("Renaming of keynode is not supported");
  }
  if (!Array.isArray(sys_idtf)) {
    sys_idtf = [sys_idtf];
  }
  let request = sys_idtf.map(x => {
    return { id: x, type: sc.ScType.NodeConst }
  });
  let result = await this.scClient.resolveKeynodes(request);
  sys_idtf.forEach(x => {
    let addr = result[x];
    if (addr.isValid()) {
      console.log('Resolved keynode: ' + x + ' = ' + addr.value);
      this[x] = addr.value;
    } else {
      throw "Can't resolve keynode " + x;
    }
  });
};

function parseURL(url) {
    var parser = document.createElement('a'),
        searchObject = {},
        queries, split, i;
    // Let the browser do the work
    parser.href = url;
    // Convert query string to object
    queries = parser.search.replace(/^\?/, '').split('&');
    for (i = 0; i < queries.length; i++) {
        split = queries[i].split('=');
        searchObject[split[0]] = split[1];
    }
    return {
        protocol: parser.protocol,
        host: parser.host,
        hostname: parser.hostname,
        port: parser.port,
        pathname: parser.pathname,
        search: parser.search,
        searchObject: searchObject,
        hash: parser.hash
    };
}

let ScHelper = function (scClient) {
  this.scClient = scClient;
};

ScHelper.prototype.init = function () {
  return Promise.resolve();
};

ScHelper.prototype.getConnectorElements = async function (arc) {
  let scTemplate = new sc.ScTemplate();
  scTemplate.triple(
      [sc.ScType.Unknown, "_source"],
      arc,
      [sc.ScType.Unknown, "_target"]
  );
  const result = await scClient.searchByTemplate(scTemplate);
  return [result[0].get("_source"), result[0].get("_target")];
};

/*! Check if there is specified connector between two objects
 * @param {String} addr1 sc-addr of source sc-element
 * @param {int} type type of sc-connector, that need to be checked for existing
 * @param {String} addr2 sc-addr of target sc-element
 * @returns Function returns Promise object. If sc-connector exists, then it would be resolved; 
 * otherwise it would be rejected
 * @note This method can be used if you want to search for constructions with constant sc-connectors only
 */
ScHelper.prototype.checkConnector = async function (addr1, type, addr2) {
  let template = new sc.ScTemplate();
  addr1 = new sc.ScAddr(addr1);
  type = new sc.ScType(type).changeConst(false);
  addr2 = new sc.ScAddr(addr2);
  template.triple(addr1, type, addr2);
  let result = await this.scClient.searchByTemplate(template);
  return result.length !== 0;
};

/*! Function to get elements of specified set
 * @param addr {String} sc-addr of set to get elements
 * @returns Returns promise objects, that resolved with a list of set elements. If 
 * failed, that promise object rejects
 */
ScHelper.prototype.getSetElements = async function (addr) {
  let template = new sc.ScTemplate();
  addr = new sc.ScAddr(addr);
  template.triple(addr, sc.ScType.VarPermPosArc, sc.ScType.VarNode);
  let result = await this.scClient.searchByTemplate(template);
  return result.map(x => x.get(2).value);
};

ScHelper.prototype.getStructureElementsByRelation = async function (structure, relation) {
  let template = new sc.ScTemplate();
  template.quintuple(
    structure,
    [sc.ScType.VarPermPosArc, "_connector_from_scene"],
    [sc.ScType.Unknown, "_main_node"],
    sc.ScType.VarPermPosArc,
    relation,
  );

  const result = await window.scClient.searchByTemplate(template);
  return result.map((triple) => {
    return {connectorFromStructure: triple.get("_connector_from_scene"), structureElement: triple.get("_main_node")};
  });
};

ScHelper.prototype.getStructureMainKeyElements = async function (structure) {
  return await this.getStructureElementsByRelation(structure, new sc.ScAddr(window.scKeynodes['rrel_main_key_sc_element']));
};

ScHelper.prototype.getStructureKeyElements = async function (structure) {
  return await this.getStructureElementsByRelation(structure, new sc.ScAddr(window.scKeynodes['rrel_key_sc_element']));
};

/*! Function resolve commands hierarchy for main menu.
 * It returns main menu command object, that contains whole hierarchy as a child objects
 */
ScHelper.prototype.getMainMenuCommands = async function () {
  const self = this;

  async function determineType(cmd_addr) {
    let isAtom = await self.checkConnector(
      window.scKeynodes["ui_user_command_class_atom"], sc.ScType.ConstPermPosArc, cmd_addr);
    if (isAtom) return "cmd_atom";
    let isNoAtom = await self.checkConnector(
      window.scKeynodes["ui_user_command_class_noatom"], sc.ScType.ConstPermPosArc, cmd_addr);
    if (isNoAtom) return "cmd_noatom";
    return 'unknown';
  }

  async function parseCommand(cmd_addr, parent_cmd) {
    let type = await determineType(cmd_addr);
    let res = {
      cmd_type: type,
      id: cmd_addr
    }
    if (parent_cmd) {
      if (!parent_cmd.hasOwnProperty('childs')) {
        parent_cmd['childs'] = [];
      }
      parent_cmd.childs.push(res);
    }

    let decompositionTemplate = new sc.ScTemplate();
    decompositionTemplate.quintuple(
      [sc.ScType.VarNode, 'decomposition'],
      sc.ScType.VarCommonArc,
      new sc.ScAddr(cmd_addr),
      sc.ScType.VarPermPosArc,
      new sc.ScAddr(window.scKeynodes["nrel_ui_commands_decomposition"]));
    decompositionTemplate.triple(
      'decomposition',
      sc.ScType.VarPermPosArc,
      [sc.ScType.VarNode, 'child_addr']
    );
    let decompositionResult = await self.scClient.searchByTemplate(decompositionTemplate);
    await Promise.all(decompositionResult.map(x => parseCommand(x.get('child_addr').value, res)));
    return res;
  }

  return parseCommand(window.scKeynodes["ui_main_menu"], null);
};

/*! Function to get available native user languages
 * @returns Returns promise object. It will be resolved with one argument - list of 
 * available user native languages. If function failed, then promise object rejects.
 */
ScHelper.prototype.getLanguages = function () {
  return window.scHelper.getSetElements(window.scKeynodes['languages']);
};

/*! Function to get list of available output languages
 * @returns Returns promise objects, that resolved with a list of available output languages. If 
 * failed, then promise rejects
 */
ScHelper.prototype.getOutputLanguages = function () {
  return window.scHelper.getSetElements(window.scKeynodes['ui_external_languages']);
};

/*! Function to find result for a specified action
 * @param action_addr sc-addr of action to get result
 * @returns Returns promise object, that resolves with sc-addr of found result structure.
 * If function fails, then promise rejects
 */
ScHelper.prototype.getResult = function (action_addr) {
  return new Promise(async (resolve) => {
    let template = new sc.ScTemplate();
    let timer = setTimeout(async () => {
      reject();
      clearTimeout(timer);
      resolve(null);
    }, 10_000);
    template.quintuple(
      new sc.ScAddr(parseInt(action_addr)),
      sc.ScType.VarCommonArc,
      [sc.ScType.VarNode, "_result"],
      sc.ScType.VarPermPosArc,
      new sc.ScAddr(window.scKeynodes['nrel_result']),
    );
    let searchByTemplate = [];
    while (!searchByTemplate.length && timer) {
      searchByTemplate = await this.scClient.searchByTemplate(template);
      if (searchByTemplate.length) {
        resolve(searchByTemplate[0].get("_result").value);
        clearTimeout(timer);
        break;
      }
    }
  });
};

ScHelper.prototype.setLinkFormat = async function (addr, format) {
  const CONNECTOR = "connector";

  let template = new sc.ScTemplate();
  template.quintuple(
    new sc.ScAddr(addr),
    [sc.ScType.VarCommonArc, CONNECTOR],
    sc.ScType.VarNode,
    sc.ScType.VarPermPosArc,
    new sc.ScAddr(window.scKeynodes['nrel_format']),
  );
  const result = await scClient.searchByTemplate(template);
  if (result.length) {
    await scClient.eraseElements([result[0].get(CONNECTOR)]);
  }

  template = new sc.ScTemplate();
  template.quintuple(
      new sc.ScAddr(addr),
      [sc.ScType.VarCommonArc, CONNECTOR],
      new sc.ScAddr(format),
      sc.ScType.VarPermPosArc,
      new sc.ScAddr(window.scKeynodes['nrel_format']),
  );
  await scClient.generateByTemplate(template);
};

ScHelper.prototype.searchNodeByIdentifier = async (linkAddr, identification) => {
    const NODE = "_node";

    const template = new sc.ScTemplate();
    template.triple(
        [sc.ScType.Unknown, NODE],
        sc.ScType.VarCommonArc,
        linkAddr,
        sc.ScType.VarPermPosArc,
        identification,
    );
    let result = await window.scClient.searchByTemplate(template);
    if (result.length) {
        return result[0].get(NODE);
    }

    return null;
};

"use strict";

/*\
 |*|
 |*|  :: Number.isInteger() polyfill ::
 |*|
 |*|  https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Number/isInteger
 |*|
 \*/

if (!Number.isInteger) {
    Number.isInteger = function isInteger(nVal) {
        return typeof nVal === "number" && isFinite(nVal) && nVal > -9007199254740992 && nVal < 9007199254740992 && Math.floor(nVal) === nVal;
    };
}

/*\
 |*|
 |*|  StringView - Mozilla Developer Network
 |*|
 |*|  Revision #8, October 6, 2014
 |*|
 |*|  https://developer.mozilla.org/en-US/docs/Web/JavaScript/Typed_arrays/StringView
 |*|  https://developer.mozilla.org/en-US/docs/User:fusionchess
 |*|
 |*|  This framework is released under the GNU Lesser General Public License, version 3 or later.
 |*|  http://www.gnu.org/licenses/lgpl-3.0.html
 |*|
 \*/

function StringView(vInput, sEncoding /* optional (default: UTF-8) */, nOffset /* optional */, nLength /* optional */) {

    var fTAView, aWhole, aRaw, fPutOutptCode, fGetOutptChrSize, nInptLen, nStartIdx = isFinite(nOffset) ? nOffset : 0,
        nTranscrType = 15;

    if (sEncoding) {
        this.encoding = sEncoding.toString();
    }

    encSwitch: switch (this.encoding) {
        case "UTF-8":
            fPutOutptCode = StringView.putUTF8CharCode;
            fGetOutptChrSize = StringView.getUTF8CharLength;
            fTAView = Uint8Array;
            break encSwitch;
        case "UTF-16":
            fPutOutptCode = StringView.putUTF16CharCode;
            fGetOutptChrSize = StringView.getUTF16CharLength;
            fTAView = Uint16Array;
            break encSwitch;
        case "UTF-32":
            fTAView = Uint32Array;
            nTranscrType &= 14;
            break encSwitch;
        default:
            /* case "ASCII", or case "BinaryString" or unknown cases */
            fTAView = Uint8Array;
            nTranscrType &= 14;
    }

    typeSwitch: switch (typeof vInput) {
        case "string":
            /* the input argument is a primitive string: a new buffer will be created. */
            nTranscrType &= 7;
            break typeSwitch;
        case "object":
            classSwitch: switch (vInput.constructor) {
                case StringView:
                    /* the input argument is a stringView: a new buffer will be created. */
                    nTranscrType &= 3;
                    break typeSwitch;
                case String:
                    /* the input argument is an objectified string: a new buffer will be created. */
                    nTranscrType &= 7;
                    break typeSwitch;
                case ArrayBuffer:
                    /* the input argument is an arrayBuffer: the buffer will be shared. */
                    aWhole = new fTAView(vInput);
                    nInptLen = this.encoding === "UTF-32" ?
                        vInput.byteLength >>> 2
                        : this.encoding === "UTF-16" ?
                            vInput.byteLength >>> 1
                            :
                            vInput.byteLength;
                    aRaw = nStartIdx === 0 && (!isFinite(nLength) || nLength === nInptLen) ?
                        aWhole
                        : new fTAView(vInput, nStartIdx, !isFinite(nLength) ? nInptLen - nStartIdx : nLength);

                    break typeSwitch;
                case Uint32Array:
                case Uint16Array:
                case Uint8Array:
                    /* the input argument is a typedArray: the buffer, and possibly the array itself, will be shared. */
                    fTAView = vInput.constructor;
                    nInptLen = vInput.length;
                    aWhole = vInput.byteOffset === 0 && vInput.length === (
                        fTAView === Uint32Array ?
                            vInput.buffer.byteLength >>> 2
                            : fTAView === Uint16Array ?
                            vInput.buffer.byteLength >>> 1
                            :
                            vInput.buffer.byteLength
                    ) ? vInput : new fTAView(vInput.buffer);
                    aRaw = nStartIdx === 0 && (!isFinite(nLength) || nLength === nInptLen) ?
                        vInput
                        : vInput.subarray(nStartIdx, isFinite(nLength) ? nStartIdx + nLength : nInptLen);

                    break typeSwitch;
                default:
                    /* the input argument is an array or another serializable object: a new typedArray will be created. */
                    aWhole = new fTAView(vInput);
                    nInptLen = aWhole.length;
                    aRaw = nStartIdx === 0 && (!isFinite(nLength) || nLength === nInptLen) ?
                        aWhole
                        : aWhole.subarray(nStartIdx, isFinite(nLength) ? nStartIdx + nLength : nInptLen);
            }
            break typeSwitch;
        default:
            /* the input argument is a number, a boolean or a function: a new typedArray will be created. */
            aWhole = aRaw = new fTAView(Number(vInput) || 0);

    }

    if (nTranscrType < 8) {

        var vSource, nOutptLen, nCharStart, nCharEnd, nEndIdx, fGetInptChrSize, fGetInptChrCode;

        if (nTranscrType & 4) { /* input is string */

            vSource = vInput;
            nOutptLen = nInptLen = vSource.length;
            nTranscrType ^= this.encoding === "UTF-32" ? 0 : 2;
            /* ...or...: nTranscrType ^= Number(this.encoding !== "UTF-32") << 1; */
            nStartIdx = nCharStart = nOffset ? Math.max((nOutptLen + nOffset) % nOutptLen, 0) : 0;
            nEndIdx = nCharEnd = (Number.isInteger(nLength) ? Math.min(Math.max(nLength, 0) + nStartIdx, nOutptLen) : nOutptLen) - 1;

        } else { /* input is stringView */

            vSource = vInput.rawData;
            nInptLen = vInput.makeIndex();
            nStartIdx = nCharStart = nOffset ? Math.max((nInptLen + nOffset) % nInptLen, 0) : 0;
            nOutptLen = Number.isInteger(nLength) ? Math.min(Math.max(nLength, 0), nInptLen - nCharStart) : nInptLen;
            nEndIdx = nCharEnd = nOutptLen + nCharStart;

            if (vInput.encoding === "UTF-8") {
                fGetInptChrSize = StringView.getUTF8CharLength;
                fGetInptChrCode = StringView.loadUTF8CharCode;
            } else if (vInput.encoding === "UTF-16") {
                fGetInptChrSize = StringView.getUTF16CharLength;
                fGetInptChrCode = StringView.loadUTF16CharCode;
            } else {
                nTranscrType &= 1;
            }

        }

        if (nOutptLen === 0 || nTranscrType < 4 && vSource.encoding === this.encoding && nCharStart === 0 && nOutptLen === nInptLen) {

            /* the encoding is the same, the length too and the offset is 0... or the input is empty! */

            nTranscrType = 7;

        }

        conversionSwitch: switch (nTranscrType) {

            case 0:

                /* both the source and the new StringView have a fixed-length encoding... */

                aWhole = new fTAView(nOutptLen);
                for (var nOutptIdx = 0; nOutptIdx < nOutptLen; aWhole[nOutptIdx] = vSource[nStartIdx + nOutptIdx++]);
                break conversionSwitch;

            case 1:

                /* the source has a fixed-length encoding but the new StringView has a variable-length encoding... */

                /* mapping... */

                nOutptLen = 0;

                for (var nInptIdx = nStartIdx; nInptIdx < nEndIdx; nInptIdx++) {
                    nOutptLen += fGetOutptChrSize(vSource[nInptIdx]);
                }

                aWhole = new fTAView(nOutptLen);

                /* transcription of the source... */

                for (var nInptIdx = nStartIdx, nOutptIdx = 0; nOutptIdx < nOutptLen; nInptIdx++) {
                    nOutptIdx = fPutOutptCode(aWhole, vSource[nInptIdx], nOutptIdx);
                }

                break conversionSwitch;

            case 2:

                /* the source has a variable-length encoding but the new StringView has a fixed-length encoding... */

                /* mapping... */

                nStartIdx = 0;

                var nChrCode;

                for (nChrIdx = 0; nChrIdx < nCharStart; nChrIdx++) {
                    nChrCode = fGetInptChrCode(vSource, nStartIdx);
                    nStartIdx += fGetInptChrSize(nChrCode);
                }

                aWhole = new fTAView(nOutptLen);

                /* transcription of the source... */

                for (var nInptIdx = nStartIdx, nOutptIdx = 0; nOutptIdx < nOutptLen; nInptIdx += fGetInptChrSize(nChrCode), nOutptIdx++) {
                    nChrCode = fGetInptChrCode(vSource, nInptIdx);
                    aWhole[nOutptIdx] = nChrCode;
                }

                break conversionSwitch;

            case 3:

                /* both the source and the new StringView have a variable-length encoding... */

                /* mapping... */

                nOutptLen = 0;

                var nChrCode;

                for (var nChrIdx = 0, nInptIdx = 0; nChrIdx < nCharEnd; nInptIdx += fGetInptChrSize(nChrCode)) {
                    nChrCode = fGetInptChrCode(vSource, nInptIdx);
                    if (nChrIdx === nCharStart) {
                        nStartIdx = nInptIdx;
                    }
                    if (++nChrIdx > nCharStart) {
                        nOutptLen += fGetOutptChrSize(nChrCode);
                    }
                }

                aWhole = new fTAView(nOutptLen);

                /* transcription... */

                for (var nInptIdx = nStartIdx, nOutptIdx = 0; nOutptIdx < nOutptLen; nInptIdx += fGetInptChrSize(nChrCode)) {
                    nChrCode = fGetInptChrCode(vSource, nInptIdx);
                    nOutptIdx = fPutOutptCode(aWhole, nChrCode, nOutptIdx);
                }

                break conversionSwitch;

            case 4:

                /* DOMString to ASCII or BinaryString or other unknown encodings */

                aWhole = new fTAView(nOutptLen);

                /* transcription... */

                for (var nIdx = 0; nIdx < nOutptLen; nIdx++) {
                    aWhole[nIdx] = vSource.charCodeAt(nIdx) & 0xff;
                }

                break conversionSwitch;

            case 5:

                /* DOMString to UTF-8 or to UTF-16 */

                /* mapping... */

                nOutptLen = 0;

                for (var nMapIdx = 0; nMapIdx < nInptLen; nMapIdx++) {
                    if (nMapIdx === nCharStart) {
                        nStartIdx = nOutptLen;
                    }
                    nOutptLen += fGetOutptChrSize(vSource.charCodeAt(nMapIdx));
                    if (nMapIdx === nCharEnd) {
                        nEndIdx = nOutptLen;
                    }
                }

                aWhole = new fTAView(nOutptLen);

                /* transcription... */

                for (var nOutptIdx = 0, nChrIdx = 0; nOutptIdx < nOutptLen; nChrIdx++) {
                    nOutptIdx = fPutOutptCode(aWhole, vSource.charCodeAt(nChrIdx), nOutptIdx);
                }

                break conversionSwitch;

            case 6:

                /* DOMString to UTF-32 */

                aWhole = new fTAView(nOutptLen);

                /* transcription... */

                for (var nIdx = 0; nIdx < nOutptLen; nIdx++) {
                    aWhole[nIdx] = vSource.charCodeAt(nIdx);
                }

                break conversionSwitch;

            case 7:

                aWhole = new fTAView(nOutptLen ? vSource : 0);
                break conversionSwitch;

        }

        aRaw = nTranscrType > 3 && (nStartIdx > 0 || nEndIdx < aWhole.length - 1) ? aWhole.subarray(nStartIdx, nEndIdx) : aWhole;

    }

    this.buffer = aWhole.buffer;
    this.bufferView = aWhole;
    this.rawData = aRaw;

    Object.freeze(this);

}

/* CONSTRUCTOR'S METHODS */

StringView.loadUTF8CharCode = function (aChars, nIdx) {

    var nLen = aChars.length, nPart = aChars[nIdx];

    return nPart > 251 && nPart < 254 && nIdx + 5 < nLen ?
        /* (nPart - 252 << 30) may be not safe in ECMAScript! So...: */
        /* six bytes */ (nPart - 252) * 1073741824 + (aChars[nIdx + 1] - 128 << 24) + (aChars[nIdx + 2] - 128 << 18) + (aChars[nIdx + 3] - 128 << 12) + (aChars[nIdx + 4] - 128 << 6) + aChars[nIdx + 5] - 128
        : nPart > 247 && nPart < 252 && nIdx + 4 < nLen ?
            /* five bytes */ (nPart - 248 << 24) + (aChars[nIdx + 1] - 128 << 18) + (aChars[nIdx + 2] - 128 << 12) + (aChars[nIdx + 3] - 128 << 6) + aChars[nIdx + 4] - 128
            : nPart > 239 && nPart < 248 && nIdx + 3 < nLen ?
                /* four bytes */(nPart - 240 << 18) + (aChars[nIdx + 1] - 128 << 12) + (aChars[nIdx + 2] - 128 << 6) + aChars[nIdx + 3] - 128
                : nPart > 223 && nPart < 240 && nIdx + 2 < nLen ?
                    /* three bytes */ (nPart - 224 << 12) + (aChars[nIdx + 1] - 128 << 6) + aChars[nIdx + 2] - 128
                    : nPart > 191 && nPart < 224 && nIdx + 1 < nLen ?
                        /* two bytes */ (nPart - 192 << 6) + aChars[nIdx + 1] - 128
                        :
                        /* one byte */ nPart;

};

StringView.putUTF8CharCode = function (aTarget, nChar, nPutAt) {

    var nIdx = nPutAt;

    if (nChar < 0x80 /* 128 */) {
        /* one byte */
        aTarget[nIdx++] = nChar;
    } else if (nChar < 0x800 /* 2048 */) {
        /* two bytes */
        aTarget[nIdx++] = 0xc0 /* 192 */ + (nChar >>> 6);
        aTarget[nIdx++] = 0x80 /* 128 */ + (nChar & 0x3f /* 63 */);
    } else if (nChar < 0x10000 /* 65536 */) {
        /* three bytes */
        aTarget[nIdx++] = 0xe0 /* 224 */ + (nChar >>> 12);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 6) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + (nChar & 0x3f /* 63 */);
    } else if (nChar < 0x200000 /* 2097152 */) {
        /* four bytes */
        aTarget[nIdx++] = 0xf0 /* 240 */ + (nChar >>> 18);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 12) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 6) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + (nChar & 0x3f /* 63 */);
    } else if (nChar < 0x4000000 /* 67108864 */) {
        /* five bytes */
        aTarget[nIdx++] = 0xf8 /* 248 */ + (nChar >>> 24);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 18) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 12) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 6) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + (nChar & 0x3f /* 63 */);
    } else /* if (nChar <= 0x7fffffff) */ { /* 2147483647 */
        /* six bytes */
        aTarget[nIdx++] = 0xfc /* 252 */ + /* (nChar >>> 30) may be not safe in ECMAScript! So...: */ (nChar / 1073741824);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 24) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 18) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 12) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + ((nChar >>> 6) & 0x3f /* 63 */);
        aTarget[nIdx++] = 0x80 /* 128 */ + (nChar & 0x3f /* 63 */);
    }

    return nIdx;

};

StringView.getUTF8CharLength = function (nChar) {
    return nChar < 0x80 ? 1 : nChar < 0x800 ? 2 : nChar < 0x10000 ? 3 : nChar < 0x200000 ? 4 : nChar < 0x4000000 ? 5 : 6;
};

StringView.loadUTF16CharCode = function (aChars, nIdx) {

    /* UTF-16 to DOMString decoding algorithm */
    var nFrstChr = aChars[nIdx];

    return nFrstChr > 0xD7BF /* 55231 */ && nIdx + 1 < aChars.length ?
        (nFrstChr - 0xD800 /* 55296 */ << 10) + aChars[nIdx + 1] + 0x2400 /* 9216 */
        : nFrstChr;

};

StringView.putUTF16CharCode = function (aTarget, nChar, nPutAt) {

    var nIdx = nPutAt;

    if (nChar < 0x10000 /* 65536 */) {
        /* one element */
        aTarget[nIdx++] = nChar;
    } else {
        /* two elements */
        aTarget[nIdx++] = 0xD7C0 /* 55232 */ + (nChar >>> 10);
        aTarget[nIdx++] = 0xDC00 /* 56320 */ + (nChar & 0x3FF /* 1023 */);
    }

    return nIdx;

};

StringView.getUTF16CharLength = function (nChar) {
    return nChar < 0x10000 ? 1 : 2;
};

/* Array of bytes to base64 string decoding */

StringView.b64ToUint6 = function (nChr) {

    return nChr > 64 && nChr < 91 ?
        nChr - 65
        : nChr > 96 && nChr < 123 ?
            nChr - 71
            : nChr > 47 && nChr < 58 ?
                nChr + 4
                : nChr === 43 ?
                    62
                    : nChr === 47 ?
                        63
                        :
                        0;

};

StringView.uint6ToB64 = function (nUint6) {

    return nUint6 < 26 ?
        nUint6 + 65
        : nUint6 < 52 ?
            nUint6 + 71
            : nUint6 < 62 ?
                nUint6 - 4
                : nUint6 === 62 ?
                    43
                    : nUint6 === 63 ?
                        47
                        :
                        65;

};

/* Base64 string to array encoding */

StringView.bytesToBase64 = function (aBytes) {

    var sB64Enc = "";

    for (var nMod3, nLen = aBytes.length, nUint24 = 0, nIdx = 0; nIdx < nLen; nIdx++) {
        nMod3 = nIdx % 3;
        if (nIdx > 0 && (nIdx * 4 / 3) % 76 === 0) {
            sB64Enc += "\r\n";
        }
        nUint24 |= aBytes[nIdx] << (16 >>> nMod3 & 24);
        if (nMod3 === 2 || aBytes.length - nIdx === 1) {
            sB64Enc += String.fromCharCode(StringView.uint6ToB64(nUint24 >>> 18 & 63), StringView.uint6ToB64(nUint24 >>> 12 & 63), StringView.uint6ToB64(nUint24 >>> 6 & 63), StringView.uint6ToB64(nUint24 & 63));
            nUint24 = 0;
        }
    }

    return sB64Enc.replace(/A(?=A$|$)/g, "=");

};


StringView.base64ToBytes = function (sBase64, nBlockBytes) {

    var
        sB64Enc = sBase64.replace(/[^A-Za-z0-9\+\/]/g, ""), nInLen = sB64Enc.length,
        nOutLen = nBlockBytes ? Math.ceil((nInLen * 3 + 1 >>> 2) / nBlockBytes) * nBlockBytes : nInLen * 3 + 1 >>> 2,
        aBytes = new Uint8Array(nOutLen);

    for (var nMod3, nMod4, nUint24 = 0, nOutIdx = 0, nInIdx = 0; nInIdx < nInLen; nInIdx++) {
        nMod4 = nInIdx & 3;
        nUint24 |= StringView.b64ToUint6(sB64Enc.charCodeAt(nInIdx)) << 18 - 6 * nMod4;
        if (nMod4 === 3 || nInLen - nInIdx === 1) {
            for (nMod3 = 0; nMod3 < 3 && nOutIdx < nOutLen; nMod3++, nOutIdx++) {
                aBytes[nOutIdx] = nUint24 >>> (16 >>> nMod3 & 24) & 255;
            }
            nUint24 = 0;
        }
    }

    return aBytes;

};

StringView.makeFromBase64 = function (sB64Inpt, sEncoding, nByteOffset, nLength) {

    return new StringView(sEncoding === "UTF-16" || sEncoding === "UTF-32" ? StringView.base64ToBytes(sB64Inpt, sEncoding === "UTF-16" ? 2 : 4).buffer : StringView.base64ToBytes(sB64Inpt), sEncoding, nByteOffset, nLength);

};

/* DEFAULT VALUES */

StringView.prototype.encoding = "UTF-8";
/* Default encoding... */

/* INSTANCES' METHODS */

StringView.prototype.makeIndex = function (nChrLength, nStartFrom) {

    var

        aTarget = this.rawData, nChrEnd, nRawLength = aTarget.length,
        nStartIdx = nStartFrom || 0, nIdxEnd = nStartIdx, nStopAtChr = isNaN(nChrLength) ? Infinity : nChrLength;

    if (nChrLength + 1 > aTarget.length) {
        throw new RangeError("StringView.prototype.makeIndex - The offset can\'t be major than the length of the array - 1.");
    }

    switch (this.encoding) {

        case "UTF-8":

            var nPart;

            for (nChrEnd = 0; nIdxEnd < nRawLength && nChrEnd < nStopAtChr; nChrEnd++) {
                nPart = aTarget[nIdxEnd];
                nIdxEnd += nPart > 251 && nPart < 254 && nIdxEnd + 5 < nRawLength ? 6
                    : nPart > 247 && nPart < 252 && nIdxEnd + 4 < nRawLength ? 5
                        : nPart > 239 && nPart < 248 && nIdxEnd + 3 < nRawLength ? 4
                            : nPart > 223 && nPart < 240 && nIdxEnd + 2 < nRawLength ? 3
                                : nPart > 191 && nPart < 224 && nIdxEnd + 1 < nRawLength ? 2
                                    : 1;
            }

            break;

        case "UTF-16":

            for (nChrEnd = nStartIdx; nIdxEnd < nRawLength && nChrEnd < nStopAtChr; nChrEnd++) {
                nIdxEnd += aTarget[nIdxEnd] > 0xD7BF /* 55231 */ && nIdxEnd + 1 < aTarget.length ? 2 : 1;
            }

            break;

        default:

            nIdxEnd = nChrEnd = isFinite(nChrLength) ? nChrLength : nRawLength - 1;

    }

    if (nChrLength) {
        return nIdxEnd;
    }

    return nChrEnd;

};

StringView.prototype.toBase64 = function (bWholeBuffer) {

    return StringView.bytesToBase64(
        bWholeBuffer ?
            (
                this.bufferView.constructor === Uint8Array ?
                    this.bufferView
                    :
                    new Uint8Array(this.buffer)
            )
            : this.rawData.constructor === Uint8Array ?
            this.rawData
            :
            new Uint8Array(this.buffer, this.rawData.byteOffset, this.rawData.length << (this.rawData.constructor === Uint16Array ? 1 : 2))
    );

};

StringView.prototype.subview = function (nCharOffset /* optional */, nCharLength /* optional */) {

    var

        nChrLen, nCharStart, nStrLen, bVariableLen = this.encoding === "UTF-8" || this.encoding === "UTF-16",
        nStartOffset = nCharOffset, nStringLength, nRawLen = this.rawData.length;

    if (nRawLen === 0) {
        return new StringView(this.buffer, this.encoding);
    }

    nStringLength = bVariableLen ? this.makeIndex() : nRawLen;
    nCharStart = nCharOffset ? Math.max((nStringLength + nCharOffset) % nStringLength, 0) : 0;
    nStrLen = Number.isInteger(nCharLength) ? Math.max(nCharLength, 0) + nCharStart > nStringLength ? nStringLength - nCharStart : nCharLength : nStringLength;

    if (nCharStart === 0 && nStrLen === nStringLength) {
        return this;
    }

    if (bVariableLen) {
        nStartOffset = this.makeIndex(nCharStart);
        nChrLen = this.makeIndex(nStrLen, nStartOffset) - nStartOffset;
    } else {
        nStartOffset = nCharStart;
        nChrLen = nStrLen - nCharStart;
    }

    if (this.encoding === "UTF-16") {
        nStartOffset <<= 1;
    } else if (this.encoding === "UTF-32") {
        nStartOffset <<= 2;
    }

    return new StringView(this.buffer, this.encoding, nStartOffset, nChrLen);

};

StringView.prototype.forEachChar = function (fCallback, oThat, nChrOffset, nChrLen) {

    var aSource = this.rawData, nRawEnd, nRawIdx;

    if (this.encoding === "UTF-8" || this.encoding === "UTF-16") {

        var fGetInptChrSize, fGetInptChrCode;

        if (this.encoding === "UTF-8") {
            fGetInptChrSize = StringView.getUTF8CharLength;
            fGetInptChrCode = StringView.loadUTF8CharCode;
        } else if (this.encoding === "UTF-16") {
            fGetInptChrSize = StringView.getUTF16CharLength;
            fGetInptChrCode = StringView.loadUTF16CharCode;
        }

        nRawIdx = isFinite(nChrOffset) ? this.makeIndex(nChrOffset) : 0;
        nRawEnd = isFinite(nChrLen) ? this.makeIndex(nChrLen, nRawIdx) : aSource.length;

        for (var nChrCode, nChrIdx = 0; nRawIdx < nRawEnd; nChrIdx++) {
            nChrCode = fGetInptChrCode(aSource, nRawIdx);
            fCallback.call(oThat || null, nChrCode, nChrIdx, nRawIdx, aSource);
            nRawIdx += fGetInptChrSize(nChrCode);
        }

    } else {

        nRawIdx = isFinite(nChrOffset) ? nChrOffset : 0;
        nRawEnd = isFinite(nChrLen) ? nChrLen + nRawIdx : aSource.length;

        for (nRawIdx; nRawIdx < nRawEnd; nRawIdx++) {
            fCallback.call(oThat || null, aSource[nRawIdx], nRawIdx, nRawIdx, aSource);
        }

    }

};

StringView.prototype.valueOf = StringView.prototype.toString = function () {

    if (this.encoding !== "UTF-8" && this.encoding !== "UTF-16") {
        /* ASCII, UTF-32 or BinaryString to DOMString */
        return String.fromCharCode.apply(null, this.rawData);
    }

    var fGetCode, fGetIncr, sView = "";

    if (this.encoding === "UTF-8") {
        fGetIncr = StringView.getUTF8CharLength;
        fGetCode = StringView.loadUTF8CharCode;
    } else if (this.encoding === "UTF-16") {
        fGetIncr = StringView.getUTF16CharLength;
        fGetCode = StringView.loadUTF16CharCode;
    }

    for (var nChr, nLen = this.rawData.length, nIdx = 0; nIdx < nLen; nIdx += fGetIncr(nChr)) {
        nChr = fGetCode(this.rawData, nIdx);
        sView += String.fromCharCode(nChr);
    }

    return sView;

};
function AppCache(opt) {
    this.opt = opt;
    this.cache = [];
}

/*
 * delete all expire keys or if key exist
 * return true if one or more keys have been removed
 */
AppCache.prototype._delExpire = function (key) {
    var rm = false,
        cache = this.cache,
        l = cache.length,
        now = Date.now(),
        obj;

    while (l--) {
        obj = cache[l];

        if (now > obj.expire || key === obj.key) {
            cache.splice(l, 1);
            rm = true;
        }
    }

    return rm;
};

AppCache.prototype.get = function (key) {
    var data,
        now = Date.now(),
        cache = this.cache,
        l = cache.length,
        obj;

    while (l--) {
        obj = cache[l];

        if (obj.key === key) {
            data = obj;
            break;
        }
    }

    if (data && now > data.expire) {
        cache.splice(l, 1);
        data = null;
    }

    return (data ? data.val : null);
};

AppCache.prototype.set = function (key, val) {
    var cache = this.cache,
        max = this.opt.max,
        data = {
            key: key,
            expire: Date.now() + this.opt.expire,
            val: val
        },
        l = cache.length;

    if (l < max) {
        cache.push(data);
    } else if (l >= max && this._delExpire(key)) {
        cache.push(data);
    } else if (l >= max) {
        cache.shift();
        cache.push(data);
    }
};

AppCache.prototype.clear = function () {
    this.cache = [];
};

function setCookie(name, value, max_age=28800){
    document.cookie = `${name}=${value};max_age=${max_age}`
}

function getCookie(name) {
    function escape(s) { return s.replace(/([.*+?\^$(){}|\[\]\/\\])/g, '\\$1'); }
    var match = document.cookie.match(RegExp('(?:^|;\\s*)' + escape(name) + '=([^;]*)'));
    return match ? match[1] : null;
}

var fQueue = (function () {

    var qnb = function () {
        var dfd = new jQuery.Deferred();
        var funcs = Array.prototype.slice.call(arguments, 0);

        function worker() {
            if (funcs.length > 0) {
                var f = funcs.shift();
                f.func.apply(f, f.args).done(function () {
                    if (f.done)
                        f.done.call(f.args);
                    setTimeout(worker, 1);
                }).fail(function () {
                    dfd.reject.call(f.args);
                });
            } else
                dfd.resolve();
        };
        worker();
        return dfd.promise();
    };
    return {
        Func: function (func, args, done) {
            return {func: func, done: done, args: args};
        },
        Queue: qnb,
    };
})();

(function dfdQueue() {

    var q,
        tasks = [],
        remain = 0,
        await = null;   // callback

    var pushImpl = function (dfd) {
        remain++;
        dfd.done()
    };

    return q = {
        push: function (dfd) {
            pushImpl(dfd);
        },

        awaitAll: function (f) {
            await = f;
        }
    };

})();
/* Object to read/write bynary data
 */
BinaryData = function (size, data) {

};

BinaryData.prototype.calcSize = function () {
};

/*!
 * Unpack data types from string, with specified format
 * @param {str} fmt String that contains data format
 * @param {ArrayBuffer} data Array buffer, that contains binary data for unpacking
 *
 * @returns Returns array, that contains unpacked data
 */
BinaryData.prototype.unpack = function (fmt, data) {
};

/*! Pack data to binary array buffer
 * @param 
 */
BinaryData.prototype.pack = function (fmt, args) {
};
TripleUtils = function () {
    this.outgoingConnectors = {};
    this.incomingConnectors = {};
    this.types = {};
    this.triples = []
};

TripleUtils.prototype = {

    appendTriple: function (tpl) {
        this.triples.push(tpl);
        this.types[tpl[0].addr] = tpl[0].type;
        this.types[tpl[1].addr] = tpl[1].type;
        this.types[tpl[2].addr] = tpl[2].type;

        this._appendOutputConnector(tpl[0].addr, tpl[1].addr, tpl[2].addr);
        this._appendInputConnector(tpl[0].addr, tpl[1].addr, tpl[2].addr);
    },

    removeTriple: function (tpl) {
        this._removeOutputConnector(tpl[0].addr, tpl[1].addr);
        this._removeInputConnector(tpl[2].addr, tpl[1].addr);
    },

    /**
     *
     * @param lookupConnectorAddr
     * @returns {src: number, connector: number, trg: number}
     */
    getConnector: function (lookupConnectorAddr) {
        return this.triples.find(([src, {addr}, trg]) => addr === lookupConnectorAddr);
    },

    /*! Search all constructions, that equal to template. 
     * @returns If something found, then returns list of results; otherwise returns null
     */
    find5_f_a_a_a_f: function (addr1, type2, type3, type4, addr5) {
        var res = [];
        // iterate all output connectors from addr1
        var list = this.outgoingConnectors[addr1];
        if (!list) return [];
        for (l in list) {
            var connector = list[l];
            if (this._compareType(type2, this._getType(connector.connector)) && this._compareType(type3, this._getType(connector.trg))) {
                // second triple iteration
                var list2 = this.incomingConnectors [connector.connector];
                if (list2) {
                    for (l2 in list2) {
                        var connector2 = list2[l2];
                        if (this._compareType(type4, this._getType(connector2.connector)) && (connector2.src === addr5)) {
                            if (!res) res = [];
                            res.push([
                                {addr: addr1, type: this._getType(addr1)},
                                {addr: connector.connector, type: this._getType(connector.connector)},
                                {addr: connector.trg, type: this._getType(connector.trg)},
                                {addr: connector2.connector, type: this._getType(connector2.connector)},
                                {addr: addr5, type: this._getType(addr5)}
                            ]);
                        }
                    }
                }
            }
        }
        return res;
    },

    find5_f_a_f_a_f: function (addr1, type2, addr3, type4, addr5) {
        const list = this.incomingConnectors [addr3];
        if (!list) return [];

        let res = [];
        for (l in list) {
            var connector = list[l];
            if (this._compareType(type2, this._getType(connector.connector)) && (addr1 === connector.src)) {
                var list2 = this.incomingConnectors [addr5];
                if (!list2) continue;

                for (l2 in list2) {
                    var connector2 = list2[l2];
                    if (this._compareType(type4, this._getType(connector2.connector)) && (addr3 === connector.src)) {
                        if (!res) res = [];
                        res.push([
                            {addr: addr1, type: this._getType(addr1)},
                            {addr: connector.connector, type: this._getType(connector.connector)},
                            {addr: addr3, type: this._getType(addr3)},
                            {addr: connector2.connector, type: this._getType(connector2.connector)},
                            {addr: addr5, type: this._getType(addr5)}
                        ]);
                    }
                }
            }
        }
    },

    find5_a_a_f_a_f: function (type1, type2, addr3, type4, addr5) {
        const list = this.find3_f_a_a(addr5, type4, type2);
        if (!list) return [];
        const res = [];
        for (const [src5, connector4, connector] of list) {
            const [src1, connector2, trg3] = this.getConnector(connector.addr);
            if (this._compareType(type1, src1.type) &&
                this._compareType(type2, connector2.type) &&
                addr3 === trg3.addr &&
                this._compareType(type4, connector4.type) &&
                addr5 === src5.addr) {
                res.push([src1, connector2, trg3, connector4, src5]);
            }
        }
        return res;
    },

    find3_f_a_f: function (addr1, type2, addr3) {
        var list = this.incomingConnectors [addr3];
        if (!list) return [];

        var res = [];
        for (l in list) {
            var connector = list[l];
            if (this._compareType(type2, connector.connector) && (addr1 === connector.src)) {
                if (!res) res = [];
                res.push([
                    {addr: addr1, type: this._getType(addr1)},
                    {addr: connector.connector, type: this._getType(connector.connector)},
                    {addr: addr3, type: this._getType(addr3)}
                ]);
            }
        }

        return res;
    },

    /*! Search all constructions, that equal to template. 
     * @returns If something found, then returns list of results; otherwise returns null
     */
    find3_f_a_a: function (addr1, type2, type3) {
        // iterate elements
        var list = this.outgoingConnectors[addr1];
        if (!list) return [];

        var res = [];
        for (l in list) {
            var connector = list[l];
            if (this._compareType(type2, this._getType(connector.connector)) && this._compareType(type3, this._getType(connector.trg))) {
                if (!res) res = [];
                res.push([
                    {addr: addr1, type: this._getType(addr1)},
                    {addr: connector.connector, type: this._getType(connector.connector)},
                    {addr: connector.trg, type: this._getType(connector.trg)}
                ]);
            }
        }
        return res;
    },

    checkAnyOutputConnector: function (srcAddr) {
        return !!this.outgoingConnectors[srcAddr];
    },

    checkAnyInputConnector: function (trgAddr) {
        return !!this.incomingConnectors [trgAddr];
    },

    checkAnyOutputConnectorType: function (srcAddr, connectorType) {
        var list = this.outgoingConnectors[srcAddr];
        if (list) {
            for (l in list) {
                if (this._checkType(connectorType, this._getType(list[l].connector)))
                    return true;
            }
        }
        return false;
    },

    checkAnyInputConnectorType: function (trgAddr, connectorType) {
        var list = this.incomingConnectors [trgAddr];
        if (list) {
            for (l in list) {
                if (this._checkType(connectorType, this._getType(list[l].connector)))
                    return true;
            }
        }
        return false;
    },

    // just for internal usage
    _compareType: function (it_type, el_type) {
        return ((it_type & el_type) === it_type);
    },

    _getType: function (addr) {
        return this.types[addr];
    },

    _appendOutputConnector: function (srcAddr, connectorAddr, trgAddr) {
        var list = this.outgoingConnectors[srcAddr];
        var connector = {src: srcAddr, connector: connectorAddr, trg: trgAddr};
        if (!list) {
            this.outgoingConnectors[srcAddr] = [connector];
        } else {
            list.push(connector);
        }
    },

    _removeOutputConnector: function (srcAddr, connectorAddr) {
        var list = this.outgoingConnectors[srcAddr];
        if (list) {
            for (e in list) {
                var connector = list[e];
                if (connector.connector === connectorAddr) {
                    this.outgoingConnectors.splice(e, 1);
                    return;
                }
            }
        }

        throw "Can't find output connectors"
    },

    _appendInputConnector: function (srcAddr, connectorAddr, trgAddr) {
        var list = this.incomingConnectors [trgAddr];
        var connector = {src: srcAddr, connector: connectorAddr, trg: trgAddr};
        if (!list) {
            this.incomingConnectors [trgAddr] = [connector];
        } else {
            list.push(connector);
        }
    },

    _removeInputConnector: function (trgAddr, connectorAddr) {
        var list = this.incomingConnectors [trgAddr];
        if (list) {
            for (e in list) {
                var connector = list[e];
                if (connector.connector === connectorAddr) {
                    this.incomingConnectors .splice(e, 1);
                    return;
                }
            }
        }

        throw "Can't find input connectors"
    }

};


let ScFileLinkTypes = {
    html: "html",
    pdf: "pdf",
    image: "image"
};

class ScFileLinkHelper {
    constructor(file, fileArrayBuffer) {
        this.file = file;
        this.type = this.getFileType();
        this.fileArrayBuffer = fileArrayBuffer;
    }

    getFileType() {
        const type = this.file.type;
        if (type.indexOf(ScFileLinkTypes.image) > -1) {
            return ScFileLinkTypes.image;
        } else if (type.indexOf(ScFileLinkTypes.html) > -1) {
            return ScFileLinkTypes.html;
        } else if (type.indexOf(ScFileLinkTypes.pdf) > -1) {
            return ScFileLinkTypes.pdf;
        } else {
            throw "Error in ScFileLinkHelper.getFileType"
        }
    }

    toBase64(arrayBuffer) {
        return btoa(
            new Uint8Array(arrayBuffer)
                .reduce((data, byte) => data + String.fromCharCode(byte), '')
        )
    }

    htmlViewResult() {
        switch (this.type) {
            case ScFileLinkTypes.html:
                return this.htmlView();
            case ScFileLinkTypes.pdf:
                return this.pdfView();
            case ScFileLinkTypes.image:
                return this.imageView();
            default:
                throw "Error in ScFileLinkHelper.htmlViewResult"
        }
    }
    htmlView() {
        this.parseHtml();
    }
    pdfView() {
        return this.toBase64(this.fileArrayBuffer);
    }
    imageView() {
        return this.toBase64(this.fileArrayBuffer)
    }
}

$.namespace('SCWeb.core');

SCWeb.core.ErrorCode = {
    Unknown: 0,
    ItemNotFound: 1,
    ItemAlreadyExists: 2
};

SCWeb.core.Debug = {

    code_map: {
        0: "Unknown",
        1: "ItemNotFound",
        2: "ItemAlreadyExists"
    },


    codeToText: function (code) {
        return this.code_map[code];
    },

    /**
     * Function to call, when any error occurs
     * @param {SCWeb.core.ErrorCode} code Code of error (error type)
     * @param message
     */
    error: function (code, message) {
        console.log("Error: " + this.codeToText(code) + ". " + message);
    }
};

const scHelper = null;
const scKeynodes = null;
const currentYear = new Date().getFullYear();

const SCgEditMode = {
    SCgModeSelect: 0,
    SCgModeConnector: 1,
    SCgModeBus: 2,
    SCgModeContour: 3,
    SCgModeLink: 4,
    SCgViewOnly: 5,

    /**
     * Check if specified mode is valid
     */
    isValid: function (mode) {
        return (mode >= this.SCgModeSelect) && (mode <= this.SCgViewOnly);
    }
};

const SCgViewMode = {
    DefaultSCgView: 0,
    DistanceBasedSCgView: 1,

    /**
     * Check if specified mode is valid
     */
    isValid: function (mode) {
        return (mode >= this.DefaultSCgView) && (mode <= this.DistanceBasedSCgView);
    }
};

// backward compatibility [scg_just_view <- scg_view_only]
const editModes = {
    'scg_just_view': SCgEditMode.SCgViewOnly,
    'scg_view_only': SCgEditMode.SCgViewOnly,
};

const viewModes = {
    'default_scg_view': SCgViewMode.DefaultSCgView,
    'distance_based_scg_view': SCgViewMode.DistanceBasedSCgView,
};

function ScClientCreate() {
    let res, rej;
    let scClient = new sc.ScClient(serverHost);
    return new Promise((resolve, reject) => {
        res = resolve(scClient);
        rej = reject;
    });
}

SCWeb.core.Main = {
    editMode: 0,
    viewMode: 0,
    window_types: [],
    idtf_modes: [],
    menu_commands: {},
    default_cmd_str: "ui_menu_view_full_semantic_neighborhood",

    /**
     * Initialize sc-web core and ui
     * @param {Object} params Initialization parameters.
     * There are required parameters:
     * - menu_container_id - id of dom element, that will contain menu items
     */
    init: function (params) {
        return new Promise((resolve) => {
            const self = this;
            SCWeb.core.Server._initialize();
            ScClientCreate().then(function (client) {
                window.scClient = client;
                window.scHelper = new ScHelper(window.scClient);
                window.scKeynodes = new ScKeynodes(window.scHelper);

                window.scKeynodes.init().then(function () {
                    window.scHelper.init().then(function () {
                        SCWeb.ui.TaskPanel.init().then(function () {
                            SCWeb.core.Server.init(function (data) {
                                self.parseUrl(data, params).then(resolve);
                            });
                        });
                    });
                });
            });
        })
    },

    parseUrl: async function (data, params) {
        const url = parseURL(window.location.href);

        url.searchObject.view_mode = viewModes[url.searchObject.view_mode] ?? SCgViewMode.DefaultSCgView;

        // backward compatibility [mode <- edit_mode]
        url.searchObject.edit_mode = url.searchObject.edit_mode ? url.searchObject.edit_mode : url.searchObject.mode;
        url.searchObject.edit_mode = editModes[url.searchObject.edit_mode] ?? SCgEditMode.SCgModeSelect;

        this.menu_commands = data.menu_commands;
        this.user = data.user;
        data.menu_container_id = params.menu_container_id;

        SCWeb.core.Translation.fireLanguageChanged(this.user.current_lang);

        if (!url.searchObject || !SCWeb.core.Main.pageShowedForUrlParameters(url.searchObject)) {
            SCWeb.core.Main.showDefaultPage(params).then(null);
        }

        await Promise.all([SCWeb.ui.Core.init(data),
            SCWeb.core.ComponentManager.init(),
            SCWeb.core.Translation.update()
        ]);
    },

    pageShowedForUrlParameters(urlObject) {
        return SCWeb.core.Main.actionParameterProcessed(urlObject)
            || SCWeb.core.Main.systemIdentifierParameterProcessed(urlObject)
            || SCWeb.core.Main.commandParameterProcessed(urlObject);
    },

    actionParameterProcessed(urlObject) {
        const action = urlObject['action'];
        if (action) {
            /// @todo Check action is really a action
            const commandState = new SCWeb.core.CommandState(action, null, null);
            SCWeb.ui.WindowManager.appendHistoryItem(action, commandState);
            return true;
        }
        return false;
    },

    systemIdentifierParameterProcessed(urlObject) {
        const lang = urlObject['lang'];
        const window_lang = window.scKeynodes[lang];
        if (window_lang) SCWeb.core.Translation.fireLanguageChanged(window_lang);

        const sysId = urlObject['sys_id'];
        if (!sysId) return false;
        SCWeb.core.Main.doDefaultCommandWithSystemIdentifier(sysId);

        const viewMode = Number(urlObject['view_mode']);
        const editMode = Number(urlObject['edit_mode']);

        SCWeb.core.Main.viewMode = viewMode ?? 0;
        SCWeb.core.Main.editMode = editMode ?? 0;

        // backward compatibility [scg_structure_view_only <- full_screen_scg]
        const fullScreenView = urlObject['full_screen_scg']
            ? urlObject['full_screen_scg']
            : urlObject['scg_structure_view_only'];
        const hideTools = urlObject['hide_tools'];
        const hideBorders = urlObject['hide_borders'];

        if (fullScreenView) {
            this.initFullScreenView(hideTools, hideBorders);
        }
        return true;
    },

    initFullScreenView(hideTools, hideBorders) {
        $('#window-header-tools').hide();
        $('#static-window-container').hide();
        $('#header').hide();
        $('#footer').hide();
        $('#window-container').css({ 'padding-right': '', 'padding-left': '' });

        this.waitForElm('.sc-contour').then(() => {
            $('#window-container').children().children().children().children().hide();
            $('.sc-contour').css({ 'height': '100%', 'width': '100%', 'position': 'absolute',
                "background-color": "none", "border": "0", "padding": "0px", "border-radius": "0px" });
            $('.scs-scn-view-toogle-button').hide().click();
            $('.sc-window').css({ "padding": "0px", "overflow": "hidden" });
            $('.panel-body').css({ "padding": "0px", "overflow": "hidden" });
            $('.scs-scn-element').css("cursor", "auto !important");
            $("[id*='tools-']").parent().css({ "height": "100%", "width": "100%" });
            $("[id*='tools-']").parent().parent().css("height", "100%");

            if (hideBorders) {
                $('.sc-contour').css({ 'border': 'none' });
                $('.panel-default').css({ 'border-color': '#FFFFFF' });
                $('.main-container').css({ 'padding-left': '0', 'padding-right': '0' });
            }
        });

        this.waitForElm('.scg-tools-panel').then(() => {
            if (hideTools) {
                $('.scg-tools-panel').css({ 'display': 'block' });
            }
        });
    },

    waitForElm(selector) {
        return new Promise(resolve => {
            if (document.querySelector(selector)) {
                return resolve(document.querySelector(selector));
            }

            const observer = new MutationObserver(() => {
                if (document.querySelector(selector)) {
                    resolve(document.querySelector(selector));
                    observer.disconnect();
                }
            });

            observer.observe(document.body, {
                childList: true,
                subtree: true
            });
        });
    },

    commandParameterProcessed(urlObject) {
        const command_identifier = urlObject['command_id'];
        if (command_identifier) {
            const parameters = Object.keys(urlObject);
            const args = [];
            for (let param of parameters) {
                if (/^arg/gi.test(param)) {
                    args.push(urlObject[param]);
                }
            }
            SCWeb.core.Main.doCommandByIdentifier(command_identifier, args);
            return true;
        }
        return false;
    },

    showDefaultPage: async function (params) {
        function start(a) {
            SCWeb.core.Main.doDefaultCommand([a]);
            if (params.first_time)
                $('#help-modal').modal({ "keyboard": true });
        }

        const argumentAddr = window.scKeynodes['ui_start_sc_element'];
        let startScElements = await window.scHelper.getSetElements(argumentAddr);
        if (startScElements.length) {
            start(startScElements[0]);
        } else {
            start(argumentAddr);
        }

        $('.copyright').text(`Copyright © 2012 - ${currentYear} OSTIS`);
    },

    /**
     * Returns sc-addr of preferred output language for current user
     */
    getDefaultExternalLang: function () {
        return this.user.default_ext_lang;
    },

    /**
     * Initiate user interface command
     * @param {String} cmd_addr sc-addr of user command
     * @param {Array} cmd_args Array of sc-addrs with command arguments
     */
    doCommand: function (cmd_addr, cmd_args) {
        SCWeb.core.Arguments.clear();
        SCWeb.core.Server.doCommand(cmd_addr, cmd_args, function (result) {
            if (result.action !== undefined) {
                const commandState = new SCWeb.core.CommandState(cmd_addr, cmd_args);
                SCWeb.ui.WindowManager.appendHistoryItem(result.action, commandState);
            } else if (result.command !== undefined) {
            } else {
                alert("There are no any result. Try another request");
            }
        });
    },

    /**
     * Initiate user interface command
     * @param {String} cmd_identifier system identifier of user command
     * @param {Array} cmd_args system identifiers of command arguments
     */
    doCommandByIdentifier: function (cmd_identifier, cmd_args) {
        const self = this;
        SCWeb.core.Arguments.clear();
        SCWeb.core.Server.resolveScAddr([cmd_identifier].concat(cmd_args)).then(function (result) {
            const cmd_addr = result[cmd_identifier];
            const resolved_args = [];
            cmd_args.forEach(function (argument) {
                resolved_args.push(result[argument]);
            })
            self.doCommand(cmd_addr, resolved_args);
        })
    },

    doCommandWithPromise: function (command_state) {
        return new Promise(function (resolve, reject) {
            SCWeb.core.Server.doCommand(command_state.command_addr, command_state.command_args, function (result) {
                if (result.action !== undefined) {
                    resolve(result.action)
                } else if (result.command !== undefined) {

                } else {
                    reject("There are no any result. Try another request");
                }
            })
        });
    },

    getTranslatedResult: function (command_state) {
        return new Promise(function (resolve) {
            SCWeb.core.Main.doCommandWithPromise(command_state).then(function (action_addr) {
                SCWeb.core.Server.getResultTranslated(action_addr, command_state.format, command_state.lang, function (result) {
                    resolve(result.link);
                })
            })
        })
    },

    /**
     * Initiate user natural language command
     * @param {String} query Natural language query
     */

    doTextCommand: function (query) {
        SCWeb.core.Server.textCommand(query, function (result) {
            if (result.action !== undefined) {
                const commandState = new SCWeb.core.CommandState(null, null, null);
                SCWeb.ui.WindowManager.appendHistoryItem(result.action, commandState);
            } else if (result.command !== undefined) {

            } else {
                alert("There are no any result. Try another request");
            }
        });
    },

    /**
     * Initiate default user interface command
     * @param {Array} cmd_args Array of sc-addrs with command arguments
     */
    doDefaultCommand: function (cmd_args) {
        if (!this.default_cmd) {
            const self = this;
            SCWeb.core.Server.resolveScAddr([this.default_cmd_str]).then(function (addrs) {
                self.default_cmd = addrs[self.default_cmd_str];
                if (self.default_cmd) {
                    self.doCommand(self.default_cmd, cmd_args);
                }
            });
        } else {
            this.doCommand(this.default_cmd, cmd_args);
        }
    },

    /**
     * Initiate default user interface command
     * @param {string} sys_id System identifier
     */
    doDefaultCommandWithSystemIdentifier: function (sys_id) {
        SCWeb.core.Server.resolveScAddr([sys_id]).then(function (addrs) {
            const resolvedId = addrs[sys_id];
            if (resolvedId) {
                SCWeb.core.Main.doDefaultCommand([resolvedId]);
            } else {
                SCWeb.core.Main.doDefaultCommandWithSystemIdentifier('ui_start_sc_element');
            }
        });
    },

    /**
    * Initiate user interface command
    * @param {String} cmd_addr sc-addr of user command
    * @param {Array} cmd_args Array of sc-addrs with command arguments
    */
    doCommandWithFormat: function (cmd_addr, cmd_args, fmt_addr) {
        SCWeb.core.Server.doCommand(cmd_addr, cmd_args, function (result) {
            if (result.action !== undefined) {
                const commandState = new SCWeb.core.CommandState(cmd_addr, cmd_args, fmt_addr);
                SCWeb.ui.WindowManager.appendHistoryItem(result.action, commandState);
            } else {
                alert("There are no any result. Try another request");
            }
        });
    },

    /**
     * Initiate default user interface command
     * @param {Array} cmd_args Array of sc-addrs with command arguments
     */
    doDefaultCommandWithFormat: function (cmd_args, fmt_addr) {
        if (!this.default_cmd) {
            var self = this;
            SCWeb.core.Server.resolveScAddr([this.default_cmd_str], function (addrs) {
                self.default_cmd = addrs[self.default_cmd_str];
                if (self.default_cmd) {
                    self.doCommandWithFormat(self.default_cmd, cmd_args, fmt_addr);
                }
            });
        } else {
            this.doCommandWithFormat(this.default_cmd, cmd_args, fmt_addr);
        }
    }
};


SCWeb.core.Server = {
    _semanticNeighborhood: {
        commandId: 'ui_menu_view_full_semantic_neighborhood',
        commandAddr: null
    },

    _listeners: [],
    _task_queue: [], // array of server tasks
    _task_active_num: 0, // number of active tasks
    _task_max_active_num: 10, // maximum number of active tasks
    _task_timeout: 0, // timer id for tasks queue
    _task_frequency: 100,   // task timer frequency

    _current_language: null,
    _identifiers_cache: null,
    _sys_identifiers_cache: null,

    _initialize: function () {
        const expire = 1000 * 60 * 5; // five minutes expire
        this._identifiers_cache = new AppCache({
            expire: expire,
            max: 3000
        });

        this._sys_identifiers_cache = new AppCache({
            expire: expire,
            max: 3000
        });

        SCWeb.core.EventManager.subscribe("translation/changed_language", this, function (lang_addr) {
            SCWeb.core.Server._current_language = parseInt(lang_addr);
        });
    },

    /*!
     * Append new listener to server tasks
     * @param {Object} listener Listener object.
     * It must have such functions as:
     * - taskStarted - function that calls on new task started. No any arguments
     * - taskFinished - function that calls on new task finished. No any arguments
     */
    appendListener: function (listener) {
        if (this._listeners.indexOf(listener) === -1) {
            this._listeners.push(listener);
        }
    },

    /*!
     * Removes specified listener
     * @param {Object} listener Listener object to remove
     */
    removeListener: function (listener) {
        const idx = this._listeners.indexOf(listener);
        if (idx >= 0) {
            this._listeners.splice(idx, 1);
        }
    },

    /*!
     * Notify all register listeners task started
     */
    _fireTaskStarted: function () {
        for (let i = 0; i < this._listeners.length; ++i) {
            $.proxy(this._listeners[i].taskStarted(), this._listeners[i]);
        }
    },

    /*!
     * Notify all registered listeners on task finished
     */
    _fireTaskFinished: function () {
        for (let i = 0; i < this._listeners.length; ++i) {
            $.proxy(this._listeners[i].taskFinished(), this._listeners[i]);
        }
    },

    /*!
     * Push new task for processing
     * @param {Object} task Object, that represents server task.
     * It contains properties such as:
     * - type - Type of ajax request (GET/POST)
     * - url - Url to call on server
     * - data - Object, that contains request parameters
     * - success - Callback function to call on success
     * - error - Callback function to call on error
     */
    _push_task: function (task) {
        this._fireTaskStarted();
        this._task_queue.push(task);

        if (!this._task_timeout) {
            const self = this;
            this._task_timeout = window.setInterval(function () {
                const tasks = self._pop_tasks();

                for (let idx in tasks) {
                    const task = tasks[idx];
                    self._task_active_num++;
                    $.ajax({
                        url: task.url,
                        data: task.data,
                        type: task.type,
                        success: task.success,
                        error: task.error,
                        complete: function () {
                            SCWeb.core.Server._fireTaskFinished();
                            self._task_active_num--;
                        }
                    });
                }

            }, this._task_frequency)
        }
    },

    /**
     * Get tasks from queue for processing.
     * It returns just tasks, that can be processed for that moment.
     * Number of returned tasks is min(_task_max_active_num - _task_active_num, _task_queue.length)
     */
    _pop_tasks: function () {
        const task_num = this._task_max_active_num - this._task_active_num;
        const res = [];
        for (let i = 0; i < Math.min(task_num, this._task_queue.length); ++i) {
            res.push(this._task_queue.shift());
        }

        if (this._task_queue.length === 0) {
            window.clearInterval(this._task_timeout);
            this._task_timeout = 0;
        }

        return res;
    },

    // ----------------------

    /*!
     * Get initial data from server
     *
     * @param {Function} callback Calls on request finished successfully. This function
     * get received data from server as a parameter
     */
    init: function (callback) {
        $.ajax({
            url: '/api/user/',
            data: null,
            type: 'GET',
            success: function (user) {
                window.scHelper.getMainMenuCommands(window.scKeynodes.ui_main_menu).then(function (menu_commands) {
                    const data = {};
                    data['menu_commands'] = menu_commands;
                    data['user'] = user;

                    window.scHelper.getLanguages().then(function (langs) {
                        SCWeb.core.Translation.setLanguages(langs);
                        data['languages'] = langs;

                        window.scHelper.getOutputLanguages().then(function (out_langs) {
                            data['external_languages'] = out_langs;
                            callback(data);
                        });
                    });
                });
            }
        });
    },

    /*!
     *
     * @param {Array} objects List of sc-addrs to resolve identifiers
     * @param {Function} callback
     */
    resolveIdentifiers: async function (objects) {
        if (!objects.length) {
            return {};
        }

        const self = this;

        const getKey = (addr) => {
            return self._current_language + '/' + addr;
        }

        let result = {}, used = {};
        let notChecked = [];
        objects.forEach(id => {
            if (used[id]) return; // skip objects, that was processed
            used[id] = true;

            let cached = this._identifiers_cache.get(getKey(id));
            if (cached) {
                if (cached !== '.') {
                    result[id] = cached;
                }
                return;
            }

            notChecked.push(id);
        });

        const getIdentifierLink = async function (addr) {
            const LINK = "_link";

            const mainIdtfTemplate = new sc.ScTemplate();
            mainIdtfTemplate.quintuple(
                addr,
                sc.ScType.VarCommonArc,
                [sc.ScType.VarNodeLink, LINK],
                sc.ScType.VarPermPosArc,
                new sc.ScAddr(window.scKeynodes["nrel_main_idtf"]),
            );
            mainIdtfTemplate.triple(
                new sc.ScAddr(self._current_language),
                sc.ScType.VarPermPosArc,
                LINK,
            );
            let result = await window.scClient.searchByTemplate(mainIdtfTemplate);

            if (result.length) {
                return result[0].get(LINK);
            }

            const mainIdtfNoLanguageTemplate = new sc.ScTemplate();
            mainIdtfNoLanguageTemplate.quintuple(
                addr,
                sc.ScType.VarCommonArc,
                [sc.ScType.VarNodeLink, LINK],
                sc.ScType.VarPermPosArc,
                new sc.ScAddr(window.scKeynodes["nrel_main_idtf"]),
            );
            let mainIdtfNoLanguageResult = await window.scClient.searchByTemplate(mainIdtfNoLanguageTemplate);

            if (mainIdtfNoLanguageResult.length) {
                return mainIdtfNoLanguageResult[0].get(LINK);
            }

            const sysIdtfTemplate = new sc.ScTemplate();
            sysIdtfTemplate.quintuple(
                addr,
                sc.ScType.VarCommonArc,
                [sc.ScType.VarNodeLink, LINK],
                sc.ScType.VarPermPosArc,
                new sc.ScAddr(window.scKeynodes["nrel_system_identifier"]),
            );

            result = await window.scClient.searchByTemplate(sysIdtfTemplate);
            if (result.length) {
                return result[0].get(LINK);
            }

            return addr;
        }

        if (arguments.length) {
            const elements = notChecked.map(id => new sc.ScAddr(parseInt(id)));
            const links = await Promise.all(elements.map(async (element) => {
                    const elementIdtf = await getIdentifierLink(element);
                    if ((elementIdtf !== element)) return elementIdtf;
                    return undefined;
                }
            ));
            let linksWithoutUndefined = links.filter(link => link !== undefined);
            if (linksWithoutUndefined.length)
            {
                const contents = await window.scClient.getLinkContents(linksWithoutUndefined);
                contents.forEach((content, index) => {
                    result[notChecked[index]] = content.data;
                });
            }
        }
        return result;
    },

    _makeArgumentsList: function (arguments_list) {
        const arguments = {};
        for (let i = 0; i < arguments_list.length; i++) {
            arguments[i.toString() + '_'] = arguments_list[i];
        }
        return arguments;
    },

    contextMenu: function (arguments_list, callback) {
        const arguments = this._makeArgumentsList(arguments_list);

        this._push_task({
            type: "GET",
            url: "api/context/",
            data: arguments,
            success: callback
        });
    },

    /*! Function to initiate user command on server
     * @param {cmd_addr} sc-addr of command
     * @param {output_addr} sc-addr of output language
     * @param {arguments_list} List that contains sc-addrs of command arguments
     * @param {callback} Function, that will be called with received data
     */
    doCommand: function (cmd_addr, arguments_list, callback) {
        const arguments = this._makeArgumentsList(arguments_list);
        arguments['cmd'] = cmd_addr;

        this._push_task({
            type: "POST",
            url: "api/cmd/do/",
            data: arguments,
            success: callback
        });
    },

    /*! Function to initiate natural language query on server
     * @param {String} query Natural language query
     * @param {callback} Function, that will be called with received data
     */
    textCommand: function (query, callback) {
        const arguments = {};
        arguments['query'] = query;

        this._push_task({
            type: "POST",
            url: "api/cmd/text/",
            data: arguments,
            success: callback
        });
    },

    /*! Function to get result translated into specified format
     * @param {action_addr} sc-addr of action to get result translated
     * @param {format_addr} sc-addr of format to translate result
     * @param {lang_addr} sc-addr of language to translate result
     * @param {callback} Function, that will be called with received data in specified format
     */
    getResultTranslated: function (action_addr, format_addr, lang_addr, callback) {
        this._push_task({
            type: "POST",
            url: "api/action/result/translate/",
            data: {"action": action_addr, "format": format_addr, "lang": lang_addr},
            success: callback
        });
    },


    /*!
     * Function that resolve sc-addrs for specified sc-elements by their system identifiers
     * @param {identifiers} List of system identifiers, that need to be resolved
     * @param {callback} Callback function that calls, when sc-addrs resolved. It
     * takes object that contains map of resolved sc-addrs as parameter
     */
    resolveScAddr: async function (idtfList) {
        let self = this;
        let notResolved = [], result = {}, used = {};

        for (let i = 0; i < idtfList.length; i++) {
            const idtf = idtfList[i];

            const cached = this._sys_identifiers_cache.get(idtf);
            if (cached) {
                result[idtf] = cached;
                continue;
            }

            if (used[idtf]) continue;
            used[idtf] = true;

            notResolved.push(idtf);
        }

        if (notResolved.length === 0) {
            return result;
        } else {
            return await (async function (result, notResolved) {
                let keynodesData = [];

                for (let i in notResolved) {
                    const idtf = notResolved[i];

                    if (idtf)
                        keynodesData.push({id: idtf, type: new sc.ScType()});
                }

                const addrs = await window.scClient.resolveKeynodes(keynodesData);
                for (let i in addrs) {
                    result[i] = addrs[i].value;
                }

                return result;
            })(result, notResolved);
        }
    },

    /*!
     * Function that get sc-link data from server
     * @param {Array} links List of sc-link addrs to get data
     * @param {Function} success Callback function, that receive map of
     * resolved sc-links format (key: sc-link addr, value: format addr).
     * @param {Function} error Callback function, that calls on error
     */
    getLinksFormat: async function (links) {
        let formats = {}

        for (const id in links) {
            const link = links[id];
            const addrStr = link.addr;

            if (addrStr && link.state !== SCgObjectState.NewInMemory) {
                const addr = new sc.ScAddr(parseInt(addrStr));

                const template = new sc.ScTemplate();
                template.quintuple(
                    addr,
                    sc.ScType.VarCommonArc,
                    sc.ScType.NodeVar,
                    sc.ScType.VarPermPosArc,
                    new sc.ScAddr(window.scKeynodes["nrel_format"]),
                );
                const format_result = await window.scClient.searchByTemplate(template);

                if (format_result.length) {
                    formats[id] = format_result[0].get(2).value;
                }
                else {
                    formats[id] = window.scKeynodes["format_txt"];
                }
            }
            else {
                let formatAddr = window.scKeynodes['format_txt'];
                switch (link.contentType) {
                    case 'image':
                        formatAddr = window.scKeynodes['format_png'];
                        break;
                    case 'pdf':
                        formatAddr = window.scKeynodes['format_pdf'];
                        break;
                    case 'html':
                        formatAddr = window.scKeynodes['format_html'];
                        break;
                }

                formats[id] = formatAddr;
            }
        }

        return formats;
    },

    /**
     * Returns list of available natural languages
     */
    getLanguages: function (callback) {
        this._push_task({
            url: "api/languages/",
            type: "GET",
            data: null,
            success: callback
        });
    },

    /**
     * Setup default natural language for user
     * @param {String} lang_addr sc-addr of new language to set up
     * @param callback
     */
    setLanguage: function (lang_addr, callback) {
        this._push_task({
            url: "api/languages/set/",
            type: "POST",
            data: {"lang_addr": lang_addr},
            success: callback
        });
    },

    /**
     * Request identifiers that contains specified substring
     * @param str Substring to find
     * @param callback
     */
    findIdentifiersSubStr: function (str, callback) {

        $.ajax({
            url: "api/idtf/find/",
            data: {"substr": str},
            type: "GET",
            success: callback
        });
    },

    /**
     * Request tooltip content for specified sc-elements
     */
    getTooltips: function (addrs, success, error) {
        let arguments = '';
        for (let i = 0; i < addrs.length; i++) {
            let arg = addrs[i];
            arguments += i.toString() + '_=' + arg + '&';
        }

        $.ajax({
            type: "POST",
            url: "api/info/tooltip/",
            data: arguments,
            success: success,
            error: error
        });
    }
};



/**
 * Object controls list of command parameters.
 * It can fires next events:
 * - "arguments/add" - this event emits on new argument add. Parameters: arg, idx
 * where:
 *        - arg - is a sc-addr of object that added as argument;
 *        - idx - is an index of the argument
 * - "arguments/remove" - this event emits on argument remove. Parameters: arg, idx
 * where:
 *        - arg - is a sc-addr of object that removed from arguments;
 *        - idx - is an index of the argument
 * - "arguments/clear" - this event emits on arguments clear (all arguments removed at once)
 */
SCWeb.core.Arguments = {
    _arguments: [],

    /**
     * Append new argument into the end of list
     *
     * @param {String} argument SC-addr of command argument
     * @return Returns index of appended argument
     */
    appendArgument: function (argument) {

        this._arguments.push(argument);

        var idx = this._arguments.length - 1;
        this._fireArgumentAppended(argument, idx);

        return idx;
    },

    /**
     * Removes first occurrence of specified argument
     *
     * @param {String} argument SC-add of argument to remove
     */
    removeArgument: function (argument) {

        var idx = this._arguments.indexOf(argument);

        if (idx >= 0) {
            var arg = this._arguments[idx];
            this._arguments.splice(idx, 1);

            this._fireArgumentAppended(arg, idx);
        }
    },

    /**
     * Remove argument by specified index
     *
     * @param {Number} idx Index of argument to remove
     */
    removeArgumentByIndex: function (idx) {

        if (idx < this._arguments.length) {
            var arg = this._arguments[idx];
            this._arguments.splice(idx, 1);

            this._fireArgumentRemoved(arg, idx);
        }
    },

    /**
     * Clears arguments list
     */
    clear: function () {

        this._arguments = [];
        this._fireArgumentCleared();
    },

    /**
     * Notify listener on argument added
     *
     * @param {String} argument Argument, that was added *
     * @param {Number} idx Index of added argument
     */
    _fireArgumentAppended: function (argument, idx) {

        SCWeb.core.EventManager.emit("arguments/add", argument, idx);
    },

    /**
     * Notify listener on argument removed
     *
     * @param {String} argument Argument, that was removed
     * @param {Number} idx Index of removed argument
     */
    _fireArgumentRemoved: function (argument, idx) {

        SCWeb.core.EventManager.emit("arguments/remove", argument, idx);
    },

    /**
     * Notify listener on argument clear
     */
    _fireArgumentCleared: function () {

        SCWeb.core.EventManager.emit("arguments/clear");
    },

    /**
     * Retrieves all available arguments to caller object.
     *
     * @returns {Array} the array of available arguments.
     */
    getArguments: function () {

        return this._arguments;
    }

};

SCWeb.core.scAddrsDict = {};

SCWeb.core.CommandState = function (command_addr, command_args, format, lang) {
    this.command_addr = command_addr;
    this.command_args = command_args || [];
    this.format = format;
    this.lang = lang
}

/**
 * Create new instance of component sandbox.
 * @param options
 */
SCWeb.core.ComponentSandbox = function (options) {
    let self = this;
    this.command_state = options.command_state;
    this.container = options.container;
    this.container_selector = "#" + SCWeb.ui.Core.selectorWindowScAddr(options.window_id);
    this.addr = options.addr ? new sc.ScAddr(parseInt(options.addr)) : new sc.ScAddr();
    this.content = options.content;
    this.contentStyle = options.contentStyle;
    this.is_struct = options.is_struct;
    this.format_addr = options.format_addr;
    this.is_editor = options.canEdit;

    this.eventGetObjectsToTranslate = null;
    this.eventApplyTranslation = null;
    this.eventArgumentsUpdate = null;
    this.eventWindowActiveChanged = null;

    if (this.is_struct) {
        this.eventStructUpdate = null;
        this.searchers = {};
        this.searchers[SCgViewMode.DefaultSCgView] = new SCWeb.core.DefaultSCgSearcher(this, this.addr);
        this.searchers[SCgViewMode.DistanceBasedSCgView] = new SCWeb.core.DistanceBasedSCgSearcher(this, this.addr);
        this.searcher = this.searchers[SCWeb.core.Main.viewMode];
        this.searcher.initAppendRemoveElementsUpdate().then(null);
    } else {
        this.eventDataAppend = null;
        this.searcher = new SCWeb.core.SCgLinkContentSearcher(this, this.addr);
    }

    this.listeners = [];
    this.keynodes = options.keynodes;

    this.listeners = [];
    this.childs = {};

    this.createWindowControls();

    // listen arguments
    this.listeners.push(SCWeb.core.EventManager.subscribe("arguments/add", this, this.onArgumentAppended));
    this.listeners.push(SCWeb.core.EventManager.subscribe("arguments/remove", this, this.onArgumentRemoved));
    this.listeners.push(SCWeb.core.EventManager.subscribe("arguments/clear", this, this.onArgumentCleared));

    // listen translation
    this.listeners.push(SCWeb.core.EventManager.subscribe("translation/update", this, this.updateTranslation));
    this.listeners.push(SCWeb.core.EventManager.subscribe("translation/get", this, function (objects) {
        let items = self.getObjectsToTranslate();
        for (let i in items) {
            objects.push(items[i]);
        }
    }));
};

SCWeb.core.ComponentSandbox.prototype = {
    constructor: SCWeb.core.ComponentSandbox
};

// ------------------ Core functions --------------------------
/**
 * Destroys component sandbox
 */
SCWeb.core.ComponentSandbox.prototype.destroy = function () {
    for (let l in this.listeners) {
        SCWeb.core.EventManager.unsubscribe(this.listeners[l]);
    }

    if (this.is_struct) this.searcher.destroyAppendRemoveElementsUpdate().then(null);
};

/**
 * Create controls for window
 */
SCWeb.core.ComponentSandbox.prototype.createWindowControls = function () {
    /*var html = '<button type="button" class="button-menu btn btn-default btn-xs" data-toggle="button"><span class="caret"></span></button>\
     <div class="btn-group-vertical btn-group-xs hidden"> \
     <button type="button" class="btn btn-success"><span class="glyphicon glyphicon-tags"></span></button> \
     </div>';
     var self = this;
     var controls = $(this.wrap_selector + ' > .sc-content-controls');
     controls.append(html).find('.button-menu').on('click', function() {
     controls.find('.btn-group-vertical').toggleClass('hidden');
     });*/

};

// ------------------ Functions to call from component --------

SCWeb.core.ComponentSandbox.prototype.canEdit = function () {
    return this.is_editor;
};

SCWeb.core.ComponentSandbox.prototype.getCurrentLanguage = function () {
    return SCWeb.core.Translation.getCurrentLanguage();
};

SCWeb.core.ComponentSandbox.prototype.getLanguages = function () {
    return SCWeb.core.Translation.getLanguages();
};

/*!
 * @param {Array} args Array of sc-addrs of command arguments.
 */
SCWeb.core.ComponentSandbox.prototype.doDefaultCommand = function (args) {
    SCWeb.core.Main.doDefaultCommand(args);
};

/*! Resolves sc-addr for all elements with attribute sc_control_sys_idtf
 */
SCWeb.core.ComponentSandbox.prototype.resolveElementsAddr = function (parentSelector) {
    SCWeb.ui.Core.resolveElementsAddr(parentSelector);
};

/*!
 * Generate html for new window container
 * @param {String} containerId ID that will be set to container
 * @param {String} classes Classes that will be added to container
 * @param {String} addr sc-addr of window
 */
SCWeb.core.ComponentSandbox.prototype.generateWindowContainer = function (containerId, containerClasses, controlClasses, addr) {
    return SCWeb.ui.WindowManager.generateWindowContainer(containerId, containerClasses, controlClasses, addr);
};

/*! Returns keynode by it system identifier
 * @param {String} sys_idtf System identifier
 * @returns If keynodes exist, then returns it sc-addr; otherwise returns null
 */
SCWeb.core.ComponentSandbox.prototype.getKeynode = function (sys_idtf) {
    var res = this.keynodes[sys_idtf];
    if (res) {
        return res;
    }
    return null;
};

SCWeb.core.ComponentSandbox.prototype.getIdentifier = function (addr, callback) {
    SCWeb.core.Server.resolveIdentifiers([addr]).then(function (idtfs) {
        callback(idtfs[addr]);
    });
};

SCWeb.core.ComponentSandbox.prototype._appendChilds = function (windows) {
    for (cntId in windows) {
        if (!windows.hasOwnProperty(cntId))
            continue;
        if (this.childs[cntId])
            delete this.childs[cntId]
        this.childs[cntId] = windows[cntId];
    }
};

SCWeb.core.ComponentSandbox.prototype.removeChild = function removeChild() {
    this.childs = {};
};

SCWeb.core.ComponentSandbox.prototype.updateResult = function () {
    var performResult = jQuery.proxy(function (result_addr) {
        this.addr = result_addr;
        this.removeChild();
    }, this);
    return SCWeb.core.Main.getTranslatedResult(this.command_state)
        .then(performResult);
}

/**
 * Create viewers for specified sc-links
 * @param {Object} containers_map Map of viewer containers (key: sc-link addr, value: id of container)
 */
SCWeb.core.ComponentSandbox.prototype.createViewersForScLinks = async function (containers_map) {
    return new Promise((resolve, reject) => {
        let self = this;
        SCWeb.ui.WindowManager.createViewersForScLinks(containers_map).then(function (windows) {
            self._appendChilds(windows);
            resolve(windows);
        }).catch(reject);
    })
};

/**
 * Create viewers for specified sc-structures
 * @param {Object} containers_map Map of viewer containers (id: id of container, value: {key: sc-struct addr, ext_lang_addr: sc-addr of external language}})
 */
SCWeb.core.ComponentSandbox.prototype.createViewersForScStructs = function (containers_map) {
    let windows = SCWeb.ui.WindowManager.createViewersForScStructs(containers_map);
    this._appendChilds(windows);
    return windows;
};

/*! Function takes content of sc-link or structure from server and call event handlers
 * {String} contentType type of content data (@see scClient.getLinkContent). If it's null, then
 * data will be returned as string
 */
SCWeb.core.ComponentSandbox.prototype.updateContent = async function (keyElement) {
    const keyElements = keyElement ? [keyElement] : null;
    if (!await this.searcher.searchContent(keyElements)) {
        await this.searchers[SCgViewMode.DefaultSCgView].searchContent();
    }
};

// ------ Translation ---------
/**
 * This function returns list of objects, that can be translated.
 * Just for internal usage in core.
 */
SCWeb.core.ComponentSandbox.prototype.getObjectsToTranslate = function () {
    if (this.eventGetObjectsToTranslate)
        return this.eventGetObjectsToTranslate();

    return [];
};

/**
 * This function apply translation to component.
 * Just for internal usage in core
 * @param {Object} translation_map Dictionary of translation
 */
SCWeb.core.ComponentSandbox.prototype.updateTranslation = function (translation_map) {
    if (this.eventApplyTranslation)
        this.eventApplyTranslation(translation_map);
};

// ----- Arguments ------
SCWeb.core.ComponentSandbox.prototype._fireArgumentsChanged = function () {
    if (this.eventArgumentsUpdate)
        this.eventArgumentsUpdate(SCWeb.core.Arguments._arguments.slice(0));
};

/**
 * Calls when new argument added
 * @param {String} argument sc-addr of argument
 * @param {Number} idx Index of argument
 */
SCWeb.core.ComponentSandbox.prototype.onArgumentAppended = function (argument, idx) {
    this._fireArgumentsChanged();
};

/**
 * Calls when new argument removed
 * @param {String} argument sc-addr of argument
 * @param {Number} idx Index of argument
 */
SCWeb.core.ComponentSandbox.prototype.onArgumentRemoved = function (argument, idx) {
    this._fireArgumentsChanged();
};

/**
 * Calls when arguments list cleared
 */
SCWeb.core.ComponentSandbox.prototype.onArgumentCleared = function () {
    this._fireArgumentsChanged();
};

// --------- Window -----------
SCWeb.core.ComponentSandbox.prototype.onWindowActiveChanged = function (is_active) {
    if (this.eventWindowActiveChanged)
        this.eventWindowActiveChanged(is_active);
};

// --------- Data -------------
SCWeb.core.ComponentSandbox.prototype.onDataAppend = function (data) {
    if (this.eventDataAppend) {
        return this.eventDataAppend(data);
    } else {
        return Promise.resolve();
    }
};

SCWeb.core.ComponentSandbox.prototype.translate = function () {
    return SCWeb.core.Translation.translate(this.getObjectsToTranslate())
        .then((namesMap) => this.updateTranslation(namesMap));
};

/**
 * This object conrols available modes for natural languages (russina, english ant etc.)
 * It can fires next events:
 * - "translation/update" - this event emits on mode changed. Parameter: dictionary, that contains new translation
 * - "translation/get" - this event emits to collect all objects for translate. Parameter: array, that need to be filled by listener
 * - "translation/changed_language" - this event emits, when current language changed. Parameter: sc-addr of current language
 * - "translation/change_language_start" - this event emits on language change start. Parameter: empty
 * (this array couldn't be cleared, listener just append new elements).
 */
SCWeb.core.Translation = {

    listeners: [],
    current_lang: null,
    languages: null,

    /** Updates all translations
     */
    update: function () {
        return new Promise((resolve, reject) => {
            // collect objects, that need to be translated
            var objects = this.collectObjects();

            // @todo need to remove duplicates from object list
            // translate
            var self = this;
            this.translate(objects).then(
              function (namesMap) {
                  self.fireUpdate(namesMap);
                  resolve();
              },
              function () {
                  reject();
              });
        })
    },

    getCurrentLanguage: function () {
        return this.current_lang;
    },

    /**
     * Do translation routines. Just for internal usage.
     * @param {Array} objects List of sc-addrs, that need to be translated
     * key is sc-addr of element and value is identifier.
     * If there are no key in returned object, then identifier wasn't found
     */
    translate: function (objects) {
        return new Promise((resolve) => {
            SCWeb.core.Server.resolveIdentifiers(objects).then(function (namesMap) {
                resolve(namesMap);
            });
        })
    },

    /** Change translation language
     * @param {String} lang_addr sc-addr of language to translate
     * @param {Function} callback Callbcak function that will be called on language change finish
     */
    setLanguage: function (lang_addr, callback) {
        var self = this;
        SCWeb.core.Server.setLanguage(lang_addr, function () {
            self.fireLanguageChanged(lang_addr);
            self.translate(self.collectObjects()).then(function (namesMap) {
                self.fireUpdate(namesMap);
                callback();
            });
        });
    },

    getLanguages() {
        return this.languages;
    },

    setLanguages(languages) {
        this.languages = languages;
    },

    /** Fires translation update event
     * @param {Dict} namesMap Dictionary that contains translations
     */
    fireUpdate: function (namesMap) {
        // notify listeners for new translations
        SCWeb.core.EventManager.emit("translation/update", namesMap);
    },

    fireLanguageChanged: function (lang_addr) {
        this.current_lang = Number.parseInt(lang_addr);
        SCWeb.core.EventManager.emit("translation/changed_language", lang_addr);
    },

    /** Collect objects for translation
     */
    collectObjects: function () {
        var objects = [];
        SCWeb.core.EventManager.emit("translation/get", objects);
        return objects;
    },

    /** Request to translate objects
     * @param {Array} objects Array of objects to translate
     */
    requestTranslate: function (objects) {
        var self = this;
        this.translate(objects, function (namesMap) {
            self.fireUpdate(namesMap);
        });
    }

};

SCWeb.core.ComponentType = {
    viewer: 0,
    editor: 1
};

SCWeb.core.ComponentManager = {

    _listener: null,
    _initialize_queue: [],
    _componentCount: 0,
    _factories_fmt: {},
    _factories_ext_lang: {},
    _ext_langs: {},
    _keynodes: [],      // array of keynodes that requested by components

    init: function () {
        return new Promise((resolve, reject)=>{
            // deffered will be resolved when all component will be registered
            this._componentCount = this._initialize_queue.length;

            // first of all we need to resolve sc-addrs of keynodes
            var keynodes = [];
            for (var i = 0; i < this._initialize_queue.length; i++) {
                var c = this._initialize_queue[i];
                keynodes = keynodes.concat(c.formats);
                if (c.getRequestKeynodes) {
                    keynodes = keynodes.concat(c.getRequestKeynodes());
                }
                if (this._initialize_queue[i].ext_lang)
                    keynodes.push(c.ext_lang);
            }

            var self = this;
            SCWeb.core.Server.resolveScAddr(keynodes).then(function (addrs) {
                self._keynodes = addrs;
                for (var i = 0; i < self._initialize_queue.length; i++) {
                    var comp_def = self._initialize_queue[i];

                    var lang_addr = addrs[comp_def.ext_lang];
                    var formats = null;
                    if (lang_addr) {
                        formats = [];
                        self._factories_ext_lang[lang_addr] = comp_def;
                    }

                    for (var j = 0; j < comp_def.formats.length; j++) {
                        var fmt = addrs[comp_def.formats[j]];

                        if (fmt) {
                            self.registerFactory(fmt, comp_def);
                            if (formats) {
                                formats.push(fmt);
                            }
                        }
                    }

                    if (formats && lang_addr) {
                        self._ext_langs[lang_addr] = formats;
                    }
                }

                resolve();
            });
        })
    },

    /**
     * Append new component initialize function
     * @param {Object} component_desc Object that define component. It contains such properties as:
     * - formats - Array of system identifiers of supported formats
     * - factory - factory function (@see SCWeb.core.ComponentManager.registerFactory)
     */
    appendComponentInitialize: function (component_def) {
        this._initialize_queue.push(component_def);
    },

    /** Register new component factory
     * @param {Array} format_addr sc-addr of supported format
     * @param {Function} func Function that will called on instance reation. If component instance created, then returns true; otherwise returns false.
     * This function takes just one parameter:
     * - sandbox - component sandbox object, that will be used to communicate with component instance
     */
    registerFactory: function (format_addr, func) {
        this._factories_fmt[format_addr] = func;
    },

    /** Check if compoenent for specified format supports structures
     */
    isStructSupported: function (format_addr) {
        var comp_def = this._factories_fmt[format_addr];
        if (!comp_def)
            throw "There are no component that supports format: " + format_addr;

        return comp_def.struct_support;
    },

    /**
     * Create new instance of component window
     * @param {Object} options          Object that contains creation options:
     *          {String} format_addr    Sc-addr of window format
     *          {Integer} addr          Sc-addr of sc-link or sc-structure, that edit or viewed with sandbox
     *          {Boolean} is_struct     If that paramater is true, then addr is an sc-addr of struct;
     *                                  otherwise the last one a sc-addr of sc-link
     *          {String} container      Id of dom object, that will contain window
     *          {Boolean} canEdit       If that value is true, then request editor creation; otherwise - viewer
     * @return Return component sandbox object for created window instance.
     * If window doesn't created, then returns null
     */
    createWindowSandboxByFormat: function (options) {
        return new Promise((resolve, reject) => {
            const comp_def = this._factories_fmt[options.format_addr];
            if (comp_def) {
                const sandbox = new SCWeb.core.ComponentSandbox({
                    container: options.container,
                    window_id: options.window_id,
                    addr: options.addr,
                    content: options.content,
                    contentStyle: options.contentStyle,
                    is_struct: options.is_struct,
                    format_addr: options.format_addr,
                    keynodes: this._keynodes,
                    command_state: options.command_state,
                    canEdit: options.canEdit
                });
                if (!comp_def.struct_support && options.is_struct)
                    throw "Component doesn't support structures: " + comp_def;

                const component = comp_def.factory(sandbox);
                if (component.editor) {
                    if (component.editor.keyboardCallbacks) {
                        SCWeb.ui.KeyboardHandler.subscribeWindow(options.window_id, component.editor.keyboardCallbacks);
                    }
                    if (component.editor.openComponentCallbacks) {
                        SCWeb.ui.OpenComponentHandler.subscribeComponent(options.window_id, component.editor.openComponentCallbacks);
                    }
                }
                if (component) {
                    resolve();

                } else throw "Can't create viewer properly"
            } else {
                reject();
            }
        });
    },

    /**
     * Create new instance of component window
     * @param {Object} options          Object that contains creation options:
     *          {String} ext_lang_addr  Sc-addr of window external language
     *          {Integer} addr           Sc-addr of sc-link or sc-structure, that edit or viewed with sandbox
     *          {Boolean} is_struct     If that parameter is true, then addr is an sc-addr of struct;
     *                                  otherwise the last one a sc-addr of sc-link
     *          {String} container      Id of dom object, that will contain window
     *          {Boolean} canEdit       If that value is true, then request editor creation; otherwise - viewer
     * @param {Function} callback Callback function that calls on creation finished
     * @return Return component sandbox object for created window instance.
     * If window doesn't created, then returns null
     */
    createWindowSandboxByExtLang: function (options, callback) {
        var comp_def = this._factories_ext_lang[options.ext_lang_addr];

        if (comp_def) {

            var sandbox = new SCWeb.core.ComponentSandbox({
                container: options.container,
                addr: options.addr,
                is_struct: options.is_struct,
                format_addr: null,
                keynodes: this._keynodes,
                canEdit: options.canEdit,
                command_state: options.command_state
            });
            if (!comp_def.struct_support && is_struct)
                throw "Component doesn't support structures: " + comp_def;

            if (comp_def.factory(sandbox))
                return sandbox;
        }

        return null;
    },

    /**
     * Returns sc-addr of primary used format for specified external language
     * @param {String} ext_lang_addr sc-addr of external language
     */
    getPrimaryFormatForExtLang: function (ext_lang_addr) {
        var fmts = this._ext_langs[ext_lang_addr];

        if (fmts && fmts.length > 0) {
            return fmts[0];
        }

        return null;
    },

    /* Returns list of external languages, that has components for sc-structure visualization */
    getScStructSupportExtLangs: function () {
        var res = [];

        for (ext_lang in this._factories_ext_lang) {
            if (this._factories_ext_lang.hasOwnProperty(ext_lang)) {
                if (this._factories_ext_lang[ext_lang].struct_support)
                    res.push(ext_lang);
            }
        }

        return res;
    },

    /**
     * Setup component listener
     * @param {Object} listener Listener object. It must to has functions:
     * - onComponentRegistered - function, that call when new component registered. It receive
     * component description object as argument
     * - onComponentUnregistered - function, that calls after one of the component was unregistered.
     * It receive component description object as argument
     */
    setListener: function (listener) {
        this._listener = listener;
    },

    /**
     * Fires event when new component registered
     */
    _fireComponentRegistered: function (compDescr) {
        if (this._listener) {
            this._listener.componentRegistered(compDescr);
        }
    },

    /**
     * Fires event when any of components unregistered
     */
    _fireComponentUnregistered: function (compDescr) {
        if (this._listener) {
            this._listener.componentUnregistered(compDescr);
        }
    }
};

SCWeb.core.DefaultSCgSearcher = function (sandbox) {
    let self = this;
    this.maxSCgTriplesNumber = 300;

    sandbox.layout = (scene) => scene.layout();
    sandbox.postLayout = (scene) => scene.updateRender();

    const splitArray = function (result, maxNumberOfTriplets) {
        if (result.length < maxNumberOfTriplets) return result;
        return result.splice(0, maxNumberOfTriplets);
    };
    const filterTriples = function (triples, filterList) {
        triples = triples.filter(triple => triple.sceneElementType.isConnector());
        if (filterList) triples = triples.filter(
            triple => !filterList.some(element => element.equal(triple.sceneElement)));
        triples = splitArray(triples, self.maxSCgTriplesNumber);
        return triples;
    };

    const searchStructureElements = async function (toFilter = false) {
        let scTemplate = new sc.ScTemplate();
        scTemplate.triple(
            sandbox.addr,
            [sc.ScType.VarPermPosArc, "_connector_from_scene"],
            [sc.ScType.Unknown, "_scene_element"],
        );
        let triples = (await scClient.searchByTemplate(scTemplate)).map((triple) => {
            return {
                connectorFromScene: triple.get("_connector_from_scene"),
                sceneElement: triple.get("_scene_element"),
                sceneElementState: SCgObjectState.FromMemory,
            };
        });
        const sceneElementTypes = await scClient.getElementsTypes(triples.map(triple => triple.sceneElement));
        triples = triples.map((triple, index) => {
            return {sceneElementType: sceneElementTypes[index], ...triple};
        });
        if (toFilter) triples = filterTriples(triples, null);
        if (!triples.length) return false;

        for (let i = 0; i < triples.length; ++i) {
            const triple = triples[i];
            sandbox.eventStructUpdate(triple);
        }

        return true;
    };

    const initAppendRemoveElementsUpdate = async function () {
        const generateArcEventRequest = new sc.ScEventSubscriptionParams(
            sandbox.addr,
            sc.ScEventType.AfterGenerateOutgoingArc,
            async (elAddr, connector, otherAddr) => {
                if (!sandbox.eventStructUpdate) return;
                const type = (await scClient.getElementsTypes([connector]))[0];
                if (!type.equal(sc.ScType.ConstPermPosArc)) return;

                sandbox.eventStructUpdate({
                    connectorFromScene: connector,
                    sceneElement: otherAddr,
                    sceneElementState: SCgObjectState.MergedWithMemory
                });
            });
        const eraseArcEventRequest = new sc.ScEventSubscriptionParams(
            sandbox.addr,
            sc.ScEventType.BeforeEraseOutgoingArc,
            async (elAddr, connector, otherAddr) => {
                if (!sandbox.eventStructUpdate) return;
                if (await window.scHelper.checkConnector(elAddr.value, sc.ScType.ConstPermPosArc, otherAddr.value)) return;

                sandbox.eventStructUpdate({
                    connectorFromScene: connector,
                    sceneElement: otherAddr,
                    sceneElementState: SCgObjectState.RemovedFromMemory
                });
            });
        [self.generateArcEvent, self.eraseArcEvent] = await window.scClient.createElementaryEventSubscriptions([generateArcEventRequest, eraseArcEventRequest]);
    };

    const destroyAppendRemoveElementsUpdate = async function () {
        let events = [];
        if (self.generateArcEvent) events.push(self.generateArcEvent);
        if (self.eraseArcEvent) events.push(self.eraseArcEvent);
        await window.scClient.destroyElementaryEventSubscriptions(events);
    };

    return {
        searchContent: async function () {
            const status = await searchStructureElements(true);
            if (status) return status;

            return await searchStructureElements(false);
        },

        initAppendRemoveElementsUpdate: async function () {
            await initAppendRemoveElementsUpdate();
        },

        destroyAppendRemoveElementsUpdate: async function () {
            await destroyAppendRemoveElementsUpdate();
        },
    };
};

SCWeb.core.DistanceBasedSCgSearcher = function (sandbox) {
    let self = this;
    this.generateArcEvent = null;
    this.eraseArcEvent = null;
    this.newElements = [];
    this.appendUpdateDelayTime = 200;

    const searchAllElements = async function () {
        let scTemplate = new sc.ScTemplate();
        scTemplate.triple(
            sandbox.addr,
            [sc.ScType.VarPermPosArc, "_connector_from_scene"],
            [sc.ScType.Unknown, "_scene_element"],
        );
        return new Set((await scClient.searchByTemplate(scTemplate)).map((triple) => triple.get("_scene_element").value));
    }

    const searchFromKeyElements = async function (keyElements, state = SCgObjectState.FromMemory) {
        let visitedElements = new Set();

        keyElements = keyElements
            ? await verifyStructureElements(sandbox.addr, keyElements)
            : await window.scHelper.getStructureMainKeyElements(sandbox.addr);
        if (!keyElements.length) keyElements = await window.scHelper.getStructureKeyElements(sandbox.addr);
        if (!keyElements.length) return visitedElements;

        const elementTypes = await scClient.getElementsTypes(keyElements.map(triple => triple.structureElement));

        let mainElements = {};
        for (let i = 0; i < keyElements.length; ++i) {
            const triple = keyElements[i];
            const connectorFromScene = triple.connectorFromStructure;
            const sceneElement = triple.structureElement;
            const sceneElementType = elementTypes[i];
            const level = SCgObjectLevel.First;

            mainElements[sceneElement.value] = {
                connectorFromScene: connectorFromScene,
                type: sceneElementType,
                state: state,
                level: level,
            };

            sandbox.eventStructUpdate({
                connectorFromScene: connectorFromScene,
                sceneElement: sceneElement,
                sceneElementType: sceneElementType,
                sceneElementState: state,
                sceneElementLevel: level,
            });
        }

        await searchAllLevelConnectors([mainElements], visitedElements, new Set());
        return visitedElements;
    };

    const searchAllLevelConnectors = async function (elementsArr, visitedElements, tracedElements) {
        let newElementsArr = [];
        for (let i = 0; i < elementsArr.length; i++) {
            let levelElements = elementsArr[i];
            for (let elementHash in levelElements) {
                elementHash = parseInt(elementHash);
                if (visitedElements.has(elementHash)) continue;
                visitedElements.add(elementHash);

                const element = new sc.ScAddr(elementHash);

                const [connectorFromScene, elementType, state, level] = Object.values(levelElements[elementHash]);
                const nextLevel = level >= SCgObjectLevel.Count - 1 ? SCgObjectLevel.Count - 1 : level + 1;

                const searchFunc = elementType.isConnector() ? searchLevelConnectorElementsConnectors : searchLevelNodeConnectors;
                const newElements = await searchFunc(
                    connectorFromScene, element, elementType, state, level, nextLevel, tracedElements);
                if (Object.keys(newElements).length) newElementsArr.push(newElements);
            }
        }

        if (newElementsArr.length) await searchAllLevelConnectors(newElementsArr, visitedElements, tracedElements);
    };

    const searchLevelNodeConnectors = async function (
        connectorFromScene, mainElement, mainElementType, state, level, nextLevel, tracedElements) {
        let nextLevelElements = {};

        await searchLevelConnectorsByDirection(
            connectorFromScene, mainElement, mainElementType,
            state, level, nextLevel, nextLevelElements, tracedElements, true
        );
        await searchLevelConnectorsByDirection(
            connectorFromScene, mainElement, mainElementType,
            state, level, nextLevel, nextLevelElements, tracedElements, false
        );

        return nextLevelElements;
    };

    const searchLevelConnectorElementsConnectors = async function (
        connectorFromScene, mainElement, mainElementType, state, level, nextLevel, tracedElements) {
        let nextLevelElements = {};

        await searchLevelConnectorElements(
            connectorFromScene, mainElement, mainElementType,
            state, level, nextLevel, nextLevelElements, tracedElements
        );
        await searchLevelConnectorsByDirection(
            connectorFromScene, mainElement, mainElementType,
            state, level, nextLevel, nextLevelElements, tracedElements, true
        );
        await searchLevelConnectorsByDirection(
            connectorFromScene, mainElement, mainElementType,
            state, level, nextLevel, nextLevelElements, tracedElements, false
        );

        return nextLevelElements;
    };

    const searchLevelConnectorElements = async function (
        connectorFromScene, mainElement, mainElementType,
        state, level, nextLevel, nextLevelElements, tracedElements
    ) {
        const mainElementHash = mainElement.value;
        if (tracedElements.has(mainElementHash)) return;
        tracedElements.add(mainElementHash);

        let sourceElement, targetElement;
        if (connectorFromScene) {
            [sourceElement, targetElement] = await window.scHelper.getConnectorElements(mainElement);
        } else {
            let scTemplateSearchConnectorElements = new sc.ScTemplate();
            scTemplateSearchConnectorElements.quintuple(
                [sc.ScType.Unknown, "_source"],
                mainElement,
                [sc.ScType.Unknown, "_target"],
                [sc.ScType.VarPermPosArc, "_connector_from_scene"],
                sandbox.addr,
            );
            const result = await scClient.searchByTemplate(scTemplateSearchConnectorElements);
            if (!result.length) return;
            [sourceElement, targetElement] = [result[0].get("_source"), result[0].get("_target")];
            connectorFromScene = result[0].get("_connector_from_scene");
        }
        [sourceElementType, targetElementType] = await scClient.getElementsTypes([sourceElement, targetElement]);

        const sourceElementHash = sourceElement.value;
        nextLevelElements[sourceElementHash] = {
            connectorFromScene: null, type: sourceElementType, state: state, level: nextLevel};

        const targetElementHash = targetElement.value;
        nextLevelElements[targetElementHash] = {
            connectorFromScene: null, type: targetElementType, state: state, level: nextLevel};

        sandbox.eventStructUpdate({
            connectorFromScene: connectorFromScene,
            sceneElement: mainElement,
            sceneElementState: state,
            sceneElementType: mainElementType,
            sceneElementLevel: level,
            sceneElementSource: sourceElement,
            sceneElementSourceType: sourceElementType,
            sceneElementSourceLevel: nextLevel,
            sceneElementTarget: targetElement,
            sceneElementTargetType: targetElementType,
            sceneElementTargetLevel: nextLevel,
        });
    };

    const searchLevelConnectorsByDirection = async function (
        connectorFromScene, mainElement, mainElementType,
        state, level, nextLevel, nextLevelElements, tracedElements, withIncomingConnector) {
        let scTemplate = new sc.ScTemplate();
        scTemplate.triple(
            sandbox.addr,
            [sc.ScType.VarPermPosArc, "_connector_from_scene"],
            [sc.ScType.Unknown, "_scene_connector"],
        );
        if (withIncomingConnector) {
            scTemplate.triple(
                [sc.ScType.Unknown, "_scene_connector_source"],
                "_scene_connector",
                mainElement,
            );
        } else {
            scTemplate.triple(
                mainElement,
                "_scene_connector",
                [sc.ScType.Unknown, "_scene_connector_target"],
            );
        }
        const constructions = await scClient.searchByTemplate(scTemplate);

        const sceneConnectorTypes = await scClient.getElementsTypes(
            constructions.map(triple => triple.get("_scene_connector")));
        const sceneConnectorElementTypes = await scClient.getElementsTypes(
            constructions.map(triple => withIncomingConnector
                ? triple.get("_scene_connector_source") : triple.get("_scene_connector_target")));

        for (let i = 0; i < constructions.length; ++i) {
            const construction = constructions[i];

            connectorFromScene = construction.get("_connector_from_scene");

            const sceneConnector = construction.get("_scene_connector");
            const sceneConnectorHash = sceneConnector.value;
            const sceneConnectorType = sceneConnectorTypes[i];

            const sceneConnectorElement = withIncomingConnector
                ? construction.get("_scene_connector_source")
                : construction.get("_scene_connector_target");
            // if we searched scene structure we'll skip it
            if (sceneConnectorElement.equal(sandbox.addr)) continue;

            if (tracedElements.has(sceneConnectorHash)) continue;
            tracedElements.add(sceneConnectorHash);
            nextLevelElements[sceneConnectorHash] = {
                connectorFromScene: connectorFromScene, type: sceneConnectorType, state: state, level: nextLevel};

            const sceneConnectorElementHash = sceneConnectorElement.value;
            const sceneConnectorElementType = sceneConnectorElementTypes[i];
            nextLevelElements[sceneConnectorElementHash] = {
                connectorFromScene: null, type: sceneConnectorElementType, state: state, level: nextLevel};

            sandbox.eventStructUpdate({
                connectorFromScene: connectorFromScene,
                sceneElement: sceneConnector,
                sceneElementType: sceneConnectorType,
                sceneElementState: state,
                sceneElementLevel: nextLevel,
                sceneElementSource: withIncomingConnector ? sceneConnectorElement : mainElement,
                sceneElementSourceType: withIncomingConnector ? sceneConnectorElementType : mainElementType,
                sceneElementSourceLevel: withIncomingConnector ? nextLevel : level,
                sceneElementTarget: withIncomingConnector ? mainElement : sceneConnectorElement,
                sceneElementTargetType: withIncomingConnector ? mainElementType : sceneConnectorElementType,
                sceneElementTargetLevel: withIncomingConnector ? level : nextLevel,
            });
        }
    };

    const verifyStructureElements = async function (structure, elements) {
        let structureElements = [];
        for (let element of elements) {
            let template = new sc.ScTemplate();
            template.triple(
                structure,
                [sc.ScType.VarPermPosArc, "_connector_from_scene"],
                [element, "_main_node"]
            );

            let result = await scClient.searchByTemplate(template);
            if (!result.length) continue;
            const triple = result[0];
            structureElements.push({
                connectorFromStructure: triple.get("_connector_from_scene"),
                structureElement: triple.get("_main_node")
            });
        }

        return structureElements;
    };

    const debounceBufferedFunc = (func, wait) => {
        let timerId;

        const clear = () => {
            clearTimeout(timerId);
        };

        const debouncedBufferedCall = (elements) => {
            clear();
            timerId = setTimeout(() => {
                func(elements.splice(0, elements.length));
            }, wait);
        };

        return [debouncedBufferedCall, clear];
    };

    const searchElementsFromElements = async function (elements) {
        const state = SCgObjectState.MergedWithMemory;

        let elementTypes = await scClient.getElementsTypes(elements);
        const connectors = elements.filter((triple, index) => elementTypes[index].isConnector());

        let structureElements = new Set();
        let connectorElements = new Set();
        for (let element of connectors) {
            const [source, target] = await window.scHelper.getConnectorElements(element);
            const [sourceHash, targetHash] = [source.value, target.value];
            if (!connectorElements.has(sourceHash) && sandbox.scene.getObjectByScAddr(sourceHash)) {
                connectorElements.add(sourceHash);
            }
            if (!connectorElements.has(targetHash) && sandbox.scene.getObjectByScAddr(targetHash)) {
                connectorElements.add(targetHash);
            }
            structureElements.add(targetHash);
        }

        const sceneElements = sandbox.scene.getScAddrs().map(hash => parseInt(hash));
        let unvisitableElements = new Set(sceneElements.filter(hash => !connectorElements.has(hash)));

        connectorElements = Array.from(connectorElements).sort(
                (a, b) => sandbox.scene.getObjectByScAddr(a).level < sandbox.scene.getObjectByScAddr(b).level ? -1 : 1);

        let mainElements = {};
        for (let elementHash of connectorElements) {
            const object = sandbox.scene.getObjectByScAddr(elementHash);
            mainElements[elementHash] = {
                connectorFromScene: new sc.ScAddr(elementHash),
                type: new sc.ScType(object.sc_type),
                state: state,
                level: object.level,
            };
            await searchAllLevelConnectors([mainElements], unvisitableElements, new Set(unvisitableElements));
            mainElements = {};
        }

        structureElements = new Set(Array.from(structureElements).filter(hash => !unvisitableElements.has(hash)));
        while (structureElements.size) {
            const [anyElement] = structureElements;
            const keyElements = [new sc.ScAddr(anyElement)];
            const visitedElements = await searchFromKeyElements(keyElements, state);
            if (!visitedElements.size) return;
            structureElements = new Set(
                Array.from(structureElements).filter(hash => !visitedElements.has(hash)));
        }
    };

    const [debouncedAppendElementsUpdate] = debounceBufferedFunc(searchElementsFromElements, this.appendUpdateDelayTime);

    const appendElementsUpdate = async function (elAddr, connector, otherAddr) {
        if (!sandbox.eventStructUpdate) return;
        const type = (await scClient.getElementsTypes([connector]))[0];
        if (!type.equal(sc.ScType.ConstPermPosArc)) return;

        self.newElements.push(otherAddr);
        debouncedAppendElementsUpdate(self.newElements);
    };

    const removeElementsUpdate = async function (elAddr, connector, otherAddr) {
        if (!sandbox.eventStructUpdate) return;
        if (await window.scHelper.checkConnector(elAddr.value, sc.ScType.ConstPermPosArc, otherAddr.value)) return;

        sandbox.eventStructUpdate({
            connectorFromScene: connector,
            sceneElement: otherAddr,
            sceneElementState: SCgObjectState.RemovedFromMemory,
        });
    }

    const initAppendRemoveElementsUpdate = async function () {
        [self.generateArcEvent, self.eraseArcEvent] = await window.scClient.createElementaryEventSubscriptions(
            [new sc.ScEventSubscriptionParams(
                sandbox.addr,
                sc.ScEventType.AfterGenerateOutgoingArc,
                appendElementsUpdate
            ), new sc.ScEventSubscriptionParams(
                sandbox.addr,
                sc.ScEventType.BeforeEraseOutgoingArc,
                removeElementsUpdate
            )]
        );
    };

    const destroyAppendRemoveElementsUpdate = async function () {
        let events = [];
        if (self.generateArcEvent) events.push(self.generateArcEvent);
        if (self.eraseArcEvent) events.push(self.eraseArcEvent);
        await window.scClient.destroyElementaryEventSubscriptions(events);
    };

    return {
        searchContent: async function (keyElements) {
            sandbox.layout = (scene) => keyElements ? scene.updateRender() : scene.layout();
            sandbox.postLayout = (scene) => keyElements ? scene.layout() : scene.updateRender();
            sandbox.onceUpdatableObjects = {};

            let status = false;
            let structureElements = await searchAllElements();
            while (structureElements.size) {
                const visitedElements = await searchFromKeyElements(keyElements);
                if (!status) status = visitedElements.size > 0;
                if (!status) return status;
                structureElements = new Set(
                    Array.from(structureElements).filter(hash => !visitedElements.has(hash)));
                const [anyElement] = structureElements;
                keyElements = [new sc.ScAddr(anyElement)];
            }

            return status;
        },

        initAppendRemoveElementsUpdate: async function () {
            await initAppendRemoveElementsUpdate();
        },

        destroyAppendRemoveElementsUpdate: async function () {
            await destroyAppendRemoveElementsUpdate();
        },
    };
};

SCWeb.core.SCgLinkContentSearcher = function (sandbox, linkAddr) {
    let self = this;
    this.contentBucket = [];
    this.contentBucketSize = 20;
    this.appendContentTimeoutId = 0;
    this.appendContentTimeout = 2;

    const forceAppendData = async (oldBucket) => {
        for (let content of oldBucket) {
            await sandbox.eventDataAppend(content.data);
        }
    };

    const sliceAndForceAppendData = async () => {
        const oldBucket = self.contentBucket.slice();
        self.contentBucket = [];
        await forceAppendData(await scClient.getLinkContents(oldBucket));
    };

    const searchData = async (element) => {
        self.contentBucket.push(element);
        if (self.appendContentTimeoutId) clearTimeout(self.appendContentTimeoutId);

        if (self.contentBucket.length > self.contentBucketSize) {
            clearTimeout(self.appendContentTimeoutId);
            await sliceAndForceAppendData();
        }
        else {
            self.appendContentTimeoutId = setTimeout(sliceAndForceAppendData, self.appendContentTimeout);
        }

        return true;
    };

    return {
        searchContent: async function () {
            return await searchData(linkAddr);
        }
    };
}

SCWeb.core.EventManager = {
    events: {},

    /**
     * Subscribe handler for specified event
     * @param {String} evt_name Event name
     * @param {Object} context Context to call callback function
     * @param {callback} callback Callback function
     * @returns Returns event object
     */
    subscribe: function (evt_name, context, callback) {
        const event = {
            event_name: evt_name,
            func: callback,
            context: context
        };

        if (!this.events[evt_name]) {
            this.events[evt_name] = [event];
        } else {
            this.events[evt_name].push(event);
        }

        return event;
    },

    /**
     * Remove subscription
     * @param {Object} event Event object
     */
    unsubscribe: function (event) {

        for (const evt in this.events) {
            const funcs = this.events[evt];
            const idx = funcs.indexOf(event);
            if (idx >= 0) {
                funcs.splice(idx, 1);
            }
        }
    },

    /**
     * Emit specified event with params
     * First param - is an event name. Other parameters will be passed into callback
     */
    emit: function () {
        const params = Array.prototype.slice.call(arguments);
        const evt = params.splice(0, 1);

        const funcs = this.events[evt];
        if (funcs) {
            for (const f in funcs) {
                const e_obj = funcs[f];
                e_obj.func.apply(e_obj.context, params);
            }
        }
    }
};

$.namespace('SCWeb.ui');

SCWeb.ui.Menu = {
    _items: null,

    /*!
     * Initialize menu in user interface
     * @param {Object} params Parameters for menu initialization.
     * There are required parameters:
     * - menu_container_id - id of dom element that will contains menu items
     * - menu_commands - object, that represent menu command hierachy (in format returned from server)
     */
    init: function (params) {
        if (SCWeb.core.Main.editMode === SCgEditMode.SCgViewOnly) return;
        
        return new Promise(resolve => {
            var self = this;

            this.menu_container_id = '#' + params.menu_container_id;

            // register for translation updates
            SCWeb.core.EventManager.subscribe("translation/get", this, function (objects) {
                var items = self.getObjectsToTranslate();
                for (var i in items) {
                    objects.push(items[i]);
                }
            });
            SCWeb.core.EventManager.subscribe("translation/update", this, function (names) {
                self.updateTranslation(names);
            });

            context.init({
                //fadeSpeed: 100,
                //filter: null,
                //above: 'auto',
                preventDoubleContext: true,
                //compress: false,
                container: '#main-container'
            });
            context.attach('[sc_addr]', this._contextMenu);

            this._build(params.menu_commands);
            resolve();
        })
    },

    _build: function (menuData) {

        this._items = [];

        var menuHtml = '<ul class="nav navbar-nav">';

        //TODO: change to children, remove intermediate 'childs'
        if (menuData.hasOwnProperty('childs')) {
            for (i in menuData.childs) {
                var subMenu = menuData.childs[i];
                menuHtml += this._parseMenuItem(subMenu);
            }
        }

        menuHtml += '</ul>';

        $(this.menu_container_id).append(menuHtml);

        this._registerMenuHandler();
    },

    _parseMenuItem: function (item) {

        this._items.push(item.id);

        var itemHtml = '';
        if (item.cmd_type === 'cmd_noatom') {
            itemHtml = '<li class="dropdown"><a sc_addr="' + item.id + '" id="' + item.id + '" class="menu-item menu-cmd-noatom dropdown-toggle" data-toggle="dropdown" href="#" ><span clas="text">' + item.id + '</span><b class="caret"></b></a>';
        } else if (item.cmd_type === 'cmd_atom') {
            itemHtml = '<li><a id="' + item.id + '"sc_addr="' + item.id + '" class="menu-item menu-cmd-atom" >' + item.id + '</a>';
        } else {
            itemHtml = '<li><a id="' + item.id + '"sc_addr="' + item.id + '" class="menu-item menu-cmd-keynode" >' + item.id + '</a>';
        }

        if (item.hasOwnProperty('childs')) {
            itemHtml += '<ul class="dropdown-menu">';
            for (i in item.childs) {
                var subMenu = item.childs[i];
                itemHtml += this._parseMenuItem(subMenu);
            }
            itemHtml += '</ul>';
        }
        return itemHtml + '</li>';
    },

    _registerMenuHandler: function () {

        $('.menu-item').click(function () {
            var sc_addr = $(this).attr('sc_addr');
            let windowId = SCWeb.ui.WindowManager.getActiveWindowId();
            let container = document.getElementById(windowId);
            if ($(this).hasClass('menu-cmd-atom')) {
                SCWeb.core.Main.doCommandWithFormat(sc_addr, SCWeb.core.Arguments._arguments,$(container).attr("sc-addr-fmt"));
            } else if ($(this).hasClass('menu-cmd-keynode')) {
                SCWeb.core.Main.doDefaultCommandWithFormat([sc_addr],$(container).attr("sc-addr-fmt"));
            }
        });
    },

    _sort: function () {

    },

    _contextMenu: function (target) {
        var dfd = new jQuery.Deferred();
        var args = SCWeb.core.Arguments._arguments.slice();
        args.push(target.attr('sc_addr'));
        SCWeb.core.Server.contextMenu(args, function (data) {

            var parseMenuItem = function (item, parentSubmenu) {
                var menu_item = {};
                let windowId = SCWeb.ui.WindowManager.getActiveWindowId();
                let container = document.getElementById(windowId);
                menu_item.action = function (e) {
                    SCWeb.core.Main.doCommandWithFormat(item, args,$(container).attr("sc-addr-fmt"));
                }

                menu_item.text = item;
                parentSubmenu.push(menu_item);
            }

            var menu = [];
            for (i in data) {
                parseMenuItem(data[i], menu);
            }

            var applyTranslation = function (item, id, text) {
                if (item.text == id) {
                    item.text = text;
                }
                if (item.subMenu) {
                    for (i in item.subMenu) {
                        applyTranslation(item.subMenu[i], id, text);
                    }
                }
            }

            SCWeb.core.Server.resolveIdentifiers(data).then(function (namesMap) {

                for (var itemId in namesMap) {
                    if (namesMap.hasOwnProperty(itemId)) {
                        for (i in menu) {
                            applyTranslation(menu[i], itemId, namesMap[itemId]);
                        }
                    }
                }

                // sort menu
                menu.sort(function (a, b) {
                    if (a.text > b.text)
                        return 1;
                    if (a.text < b.text)
                        return -1;
                    return 0;
                });

                menu.unshift({
                    text: '<span class="glyphicon glyphicon-pushpin" aria-hidden="true"></span>',
                    action: function (e) {
                        SCWeb.core.Arguments.appendArgument(target.attr('sc_addr'));
                    }
                });

                dfd.resolve(menu);
            });
        });
        return dfd.promise();
    },

    // ---------- Translation listener interface ------------
    updateTranslation: function (namesMap) {
        // apply translation
        $(this.menu_container_id + ' [sc_addr]').each(function (index, element) {
            var addr = $(element).attr('sc_addr');
            if (namesMap[addr]) {
                $(element).text(namesMap[addr]);
            }
        });

    },

    /**
     * @return Returns list obj sc-elements that need to be translated
     */
    getObjectsToTranslate: function () {
        return this._items;
    }
};

SCWeb.ui.LanguagePanel = {

    /*!
     * Initialize settings panel.
     * @param {Object} params Parameters for panel initialization.
     * There are required parameters:
     * - languages - list of available natural languages
     */
    init: function (params) {
        return new Promise(resolve => {
            this.languages = params.languages;

            var html = '';
            for (i in this.languages) {
                var addr = this.languages[i];

                html += '<option sc_addr="' + addr + '">' + addr + '</option>';
            }

            // append languages to select
            $('#language-select').html(html)
              .val(params.user.current_lang)
              .change(function () {
                  SCWeb.ui.Locker.show();
                  var addr = $('#language-select option:selected').attr("sc_addr");
                  $('#language-select').attr('disabled', true);
                  SCWeb.core.Translation.setLanguage(addr, function () {
                      $('#language-select').removeAttr('disabled', true);
                      SCWeb.ui.Locker.hide();
                  });
              });

            // listen translation events
            SCWeb.core.EventManager.subscribe("translation/update", this, this.updateTranslation);
            SCWeb.core.EventManager.subscribe("translation/get", this, function (objects) {
                $('#language-select [sc_addr]').each(function (index, element) {
                    objects.push($(element).attr('sc_addr'));
                });
            });
            resolve();
        })
    },


    // ---------- Translation listener interface ------------
    updateTranslation: function (namesMap) {
        // apply translation
        this.updateSearchInput();
        $('#language-select [sc_addr]').each(function (index, element) {
            var addr = $(element).attr('sc_addr');
            if (namesMap[addr]) {
                $(element).text(namesMap[addr].replace('user::', '').replace('session::', ''));
            }
        });

    },

    updateSearchInput: function () {
        var keynodes = ['ui_control_search'];
        SCWeb.core.Server.resolveScAddr(keynodes).then(function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers([keynodes['ui_control_search']]).then(function (idf) {
                $("#search-input").attr('placeholder', idf[keynodes['ui_control_search']]);
            });
        })
    }

};

SCWeb.ui.Locker = {
    counter: 0,

    update: function () {
        if (this.counter > 0) {
            $('#sc-ui-locker').addClass('shown');
        } else {
            $('#sc-ui-locker').removeClass('shown');
        }
    },

    show: function () {
        this.counter++;
        this.update();
    },

    hide: function () {
        if (this.counter) {
            this.counter--;
        }
        this.update();
    }
};

SCWeb.ui.Core = {

    init: function (data) {
        let self = this;
        return new Promise(resolve => {

            this.tooltip_interval = null;
            this.tooltip_element = null;

            function clearTooltipInterval() {
                if (self.tooltip_interval) {
                    clearInterval(self.tooltip_interval);
                    self.tooltip_interval = null;
                }
            }

            function destroyTooltip() {
                if (self.tooltip_element) {
                    self.tooltip_element.tooltip('destroy');
                    self.tooltip_element = null;
                }
            }

            Promise.all([SCWeb.ui.Menu.init(data),
              SCWeb.ui.ArgumentsPanel.init(),
              SCWeb.ui.UserPanel.init(data),
              SCWeb.ui.LanguagePanel.init(data),
              SCWeb.ui.WindowManager.init(data),
              SCWeb.ui.SearchPanel.init(),
              SCWeb.ui.ExpertModePanel.init(),
              SCWeb.ui.KeyboardHandler.init(SCWeb.ui.WindowManager),
              self.resolveElementsAddr('body'),
            ]).then(function () {
                
                // Display interface elements only after page load
                $('#header, #search-panel, #footer').removeClass('no_display');

                // listen clicks on sc-elements
                var sc_elements_cmd_selector = '[sc_addr]:not(.sc-window, .sc-no-default-cmd)';
                $('#window-container,#help-modal').delegate(sc_elements_cmd_selector, 'click', function (e) {
                    if (!SCWeb.ui.ArgumentsPanel.isArgumentAddState()) {
                        SCWeb.core.Main.doDefaultCommand([$(e.currentTarget).attr('sc_addr')]);
                        e.stopPropagation();
                    }
                });

                var sc_elements_arg_selector = '[sc_addr]:not(.sc-window)';
                $('body').delegate(sc_elements_arg_selector, 'click', function (e) {
                    if (SCWeb.ui.ArgumentsPanel.isArgumentAddState()) {
                        SCWeb.core.Arguments.appendArgument($(this).attr('sc_addr'));
                        e.stopPropagation();
                    }
                });

                var sc_elements_tooltip_selector = '[sc_addr]:not(.sc-window, .ui-no-tooltip)';
                $('body')
                  .delegate(sc_elements_tooltip_selector, 'mouseover', function (e) {

                      clearTooltipInterval();
                      self.tooltip_element = $(this);
                      self.tooltip_interval = setInterval(function () {
                          clearInterval(self.tooltip_interval);
                          self.tooltip_interval = null;
                          var addr = self.tooltip_element.attr('sc_addr');
                          if (addr) {
                              SCWeb.core.Server.resolveIdentifiers([addr]).then(function (idf) {
                                  if (self.tooltip_element) { // check mouseout destroy
                                      self.tooltip_element.tooltip({
                                         placement: ($(self.tooltip_element).hasClass("btn-default") || $(self.tooltip_element).is("#arguments_clear_button")) ? 'right' : "auto",
                                         title: idf[addr]
                                     }).tooltip('show');
                                  }
                              }, function () {
                                  destroyTooltip();
                              });
                          }
                      }, 1000);
                  }).delegate(sc_elements_tooltip_selector, 'mouseout', function (e) {
                    clearTooltipInterval();
                    destroyTooltip();
                }).delegate(sc_elements_tooltip_selector, 'keydown', function (e) {
                    clearTooltipInterval();
                    destroyTooltip();
                });

                $('#help-modal').on('shown.bs.modal', function () {
                    var body = $('#help-modal-body');
                    if (body.hasClass('modal-empty')) {
                        body.addClass('loading');
                        // try to find content
                        SCWeb.core.Server.resolveScAddr(['ui_start_help']).then(function (addrs) {
                            const linkAddr = addrs['ui_start_help'];
                            if (linkAddr) {
                                body.html('<div id="help-modal-content" class="sc-window" sc_addr="' + linkAddr + '"> </div>');
                                SCWeb.ui.WindowManager.createViewersForScLinks(
                                    {'help-modal-content': {'addr': linkAddr, contentStyle: {'maxWidth': '100%', 'maxHeight': '100%'}}})
                                .then(function () {
                                    body.removeClass('loading');
                                    body.removeClass('modal-empty');
                                });
                            }
                        });
                    }
                });

                resolve();
            });
        })
    },

    /*! Returns selector to select all elements, that has sc_addr in specified window, excluding all
     * sc_addr elements in child windows
     */
    selectorWindowScAddr: function (windowId) {
        return windowId + ' [sc_addr]:not(' + windowId + ' .sc-content [sc_addr])';
    },

    /*! Resolve sc-addrs for elements, that has sc_control_sys_idtf attribute in specified container
     * @param {String} parentSelector String that contains selector for parent element
     */
    resolveElementsAddr: function (parentSelector) {
        return new Promise(resolve => {
            var attr_name = 'sc_control_sys_idtf';
            var identifiers = [];
            var elements = [];
            $(parentSelector + ' [' + attr_name + ']').each(function () {
                identifiers.push($(this).attr(attr_name));
                elements.push($(this));
            });

            SCWeb.core.Server.resolveScAddr(identifiers).then(function (addrs) {
                for (e in elements) {
                    var el = elements[e];
                    var addr = addrs[el.attr(attr_name)];
                    if (addr) {
                        el.attr('sc_addr', addr);
                    } else {
                        el.addClass('sc-not-exist-control');
                    }
                }
                resolve();
            });
        })
    }
};

const searchNodeByAnyIdentifier = async (string) => {
    return new Promise(async (resolve) => {
        let linkAddrs = await window.scClient.searchLinksByContents([string]);
        let addr = null;

        if (linkAddrs.length) {
            linkAddrs = linkAddrs[0];

            if (linkAddrs.length) {
                addr = linkAddrs[0];
                addr = await window.scHelper.searchNodeByIdentifier(addr, window.scKeynodes["nrel_system_identifier"]);
                if (!addr) {
                    addr = await window.scHelper.searchNodeByIdentifier(addr, window.scKeynodes["nrel_main_idtf"]);
                }

                if (!addr) {
                    addr = linkAddrs[0];
                }
            }

            resolve(addr);
        }
    });
};

const translateByKeyWord = async (event, string) => {
    if (string) {
        searchNodeByAnyIdentifier(string).then((selectedAddr) => {
            SCWeb.core.Main.doDefaultCommand([selectedAddr.value]);
        });
    }
    event.stopPropagation();
    $('.typeahead').val('');
    $('.tt-dropdown-menu').hide();
};

const debouncePanel = (fn, ms) => {
    let timeout;
    return function () {
        const fnCall = () => { fn.apply(this, arguments) }
        clearTimeout(timeout);
        timeout = setTimeout(fnCall, ms)
    };
}

SCWeb.ui.SearchPanel = {
    init: function () {
        return new Promise(resolve => {
            $('.typeahead').typeahead({
                minLength: 1,
                highlight: true,
            },
                {
                    name: 'idtf',
                    source: debouncePanel(function (str, callback) {
                        $('#search-input').addClass('search-processing');
                        window.scClient.searchLinkContentsByContentSubstrings([str]).then((strings) => {
                            const maxContentSize = 200;
                            const keys = strings.length ? strings[0].filter((string) => string.length < maxContentSize) : [];
                            callback(keys);
                            $('#search-input').removeClass('search-processing');
                        });
                    }, 500),
                    templates: {
                        suggestion: function (string) {
                            return '<p>' + string + '</p>';
                        }
                    }
                }
            ).bind('typeahead:selected', async function (event, string, dataset) {
                await translateByKeyWord(event, string);
            }).keypress(async function (event) {
                if (event.which === 13) {
                    await translateByKeyWord(event, $('#search-input').val());
                }
            });

            resolve();
        })
    },

};

/**
 * Created by rizhi-kote on 24.4.16.
 */
SCWeb.ui.KeyboardHandler = {

    events: {},

    init: function () {
        var self = this;

        $(window)
            .on('keydown', function (d3_event) {
                self.emit('onkeydown', d3_event);
            })
            .on('keyup', function (d3_event) {
                self.emit('onkeyup', d3_event);
            })
            .on('keypress', function (d3_event) {
                self.emit('onkeypress', d3_event);
            });
    },


    onKeyDown: function (d3_event) {
        this.getActiveWindow().onKeyDown(d3_event);
    },

    onKeyUp: function (d3_event) {
        this.getActiveWindow().onKeyUp(d3_event);
    },

    onKeyPress: function (d3_event) {
        this.getActiveWindow().onKeyPress(d3_event);
    },

    subscribe: function (evt_name, window_id, callback) {

        var event = {
            event_name: evt_name,
            func: callback,
            window_id: window_id
        };

        if (!this.events[evt_name]) {
            this.events[evt_name] = {};
            this.events[evt_name][window_id] = event;
        } else {
            this.events[evt_name][window_id] = event;
        }
    },

    subscribeWindow: function (window_id, callbackArray) {

        for (var eventType in callbackArray) {
            var func = callbackArray[eventType];
            if (typeof func !== typeof function () {
                }) {
                continue;
            }
            this.subscribe(eventType, window_id, func);
        }
    },

    /**
     * Remove subscription
     * @param {Object} event Event object
     */
    unsubscribe: function (event) {

        this.events[event.event_name][event.window_id] = undefined;
    },

    /**
     * Emit specified event with params
     * First param - is an event name. Other parameters will be passed into callback
     */
    emit: function (eventType, d3_event) {
        var windowId = SCWeb.ui.WindowManager.getActiveWindowId();
        if (!this.events[eventType] || !this.events[eventType][windowId])
            return;
        var callBack = this.events[eventType][windowId].func;
        if (callBack) {
            callBack(d3_event);
        }
    }
}

SCWeb.ui.TaskPanel = {
    _container: '#task_panel',
    _text_container: '#task_num',
    _task_num: 0,

    init: function (callback) {
        return new Promise(resolve => {
            SCWeb.core.Server.appendListener(this);
            resolve();
        })
    },

    /*!
     * Updates task panel view
     */
    updatePanel: function () {
//        if (this._task_num == 0) {
//            $(this._container).removeClass('active');
//        }else{
//            $(this._container).addClass('active');
//        }
//        var text = ''
//        if (this._task_num > 0)
//            text = this._task_num.toString();
//        $(this._text_container).text(text);
    },

    // ------- Server listener --------
    taskStarted: function () {
        this._task_num++;
        this.updatePanel();
        //SCWeb.ui.Locker.show();
    },

    taskFinished: function () {
        this._task_num--;
        this.updatePanel();
        //SCWeb.ui.Locker.hide();
    }
};

SCWeb.ui.ArgumentsPanel = {
    _container: '#arguments_buttons',

    init: function () {
        this.argument_add_state = false;
        var self = this;
        return new Promise((resolve, reject)=>{

            // listen events from arguments
            SCWeb.core.EventManager.subscribe("arguments/add", this, this.onArgumentAppended);
            SCWeb.core.EventManager.subscribe("arguments/remove", this, this.onArgumentRemoved);
            SCWeb.core.EventManager.subscribe("arguments/clear", this, this.onArgumentsCleared);


            // listen events from translation
            SCWeb.core.EventManager.subscribe("translation/update", this, this.updateTranslation);
            SCWeb.core.EventManager.subscribe("translation/get", this, function (objects) {
                var items = self.getObjectsToTranslate();
                for (var i in items) {
                    objects.push(items[i]);
                }
            });

            $('#arguments_clear_button').click(function () {
                if (self.isArgumentAddState())
                    return;
                SCWeb.core.Arguments.clear();
            });
            $('#arguments_add_button').click(function () {
                self.argument_add_state = !self.argument_add_state;
                self.updateArgumentAddState();
            });

            $(document).on("click", ".argument-item", function (event) {
                var idx = $(this).attr('arg_idx');
                SCWeb.core.Arguments.removeArgumentByIndex(parseInt(idx));
            });

            resolve();
        })
    },

    isArgumentAddState: function () {
        return this.argument_add_state;
    },

    updateArgumentAddState: function () {
        var add_button = $("#arguments_add_button");
        if (this.argument_add_state) {
            add_button.addClass('argument-wait');
        } else {
            add_button.removeClass('argument-wait');
        }
    },

    // ------- Arguments listener interface -----------
    onArgumentAppended: function (argument, idx) {

        this.argument_add_state = false;
        this.updateArgumentAddState();

        var idx_str = idx.toString();
        var self = this;

        var new_button = '<button class="btn btn-primary argument-item argument-translate-state" sc_addr="'
            + argument
            + '" arg_idx="'
            + idx_str
            + '" id="argument_'
            + idx_str
            + '"></button>';
        $(this._container).append(new_button);

        // translate added argument
        SCWeb.core.Translation.translate([argument]).then(function (namesMap) {

            var value = argument;
            if (namesMap[argument]) {
                value = namesMap[argument];
            }

            $(self._container + " [sc_addr='" + argument + "']").text(value).removeClass('argument-translate-state');
        });

    },

    onArgumentRemoved: function (argument, idx) {

        $('#argument_' + idx.toString()).remove();
        // update indicies
        $(this._container + ' [arg_idx]').each(function (index, element) {

            var v = parseInt($(this).attr('arg_idx'));

            if (v > idx) {
                v = v - 1;
                $(this).attr('arg_idx', v.toString());
                $(this).attr('id', 'argument_' + v.toString());
            }
        });
    },

    onArgumentsCleared: function () {

        $(this._container).empty();
    },

    // ------- Translation listener interface ---------
    updateTranslation: function (namesMap) {

        // apply translation
        $('#arguments_buttons [sc_addr]').each(function (index, element) {

            var addr = $(element).attr('sc_addr');
            if (namesMap[addr]) {
                $(element).text(namesMap[addr]);
            }
        });
    },

    getObjectsToTranslate: function () {

        return SCWeb.core.Arguments._arguments;
    }

};

SCWeb.ui.WindowManager = {

    // dictionary that contains information about windows corresponding to history items
    windows: [],
    window_count: 0,
    MAX_WINDOWS: 20,
    window_active_formats: {},
    sandboxes: {},
    active_window_id: null,
    active_history_addr: null,


    // function to create hash from action addr and format addr
    hash_addr: function (action_addr, fmt_addr) {
        return action_addr + '_' + fmt_addr;
    },

    isWindowExist: function (id) {
        return this.windows.indexOf(id) !== -1;
    },
    init: function (params) {
        return new Promise((resolve, reject) => {
            this.ext_langs = params.external_languages;

            this.history_tabs_id = '#history-items';
            this.history_tabs = $(this.history_tabs_id);

            this.window_container_id = '#window-container';
            this.window_container = $(this.window_container_id);

            var self = this;

            // external language
            var ext_langs_items = '';
            for (idx in this.ext_langs) {
                var addr = this.ext_langs[idx];
                ext_langs_items += '<li><a href="#" sc_addr="' + addr + '">' + addr + '</a></li>';
            }
            $('#history-item-langs').html(ext_langs_items).find('[sc_addr]').click(function (event) {

                if (SCWeb.ui.ArgumentsPanel.isArgumentAddState()) return;

                var action_addr = self.active_history_addr;
                var lang_addr = $(this).attr('sc_addr');

                var fmt_addr = SCWeb.core.ComponentManager.getPrimaryFormatForExtLang(lang_addr);
                var lang = SCWeb.core.Translation.getCurrentLanguage();
                if (fmt_addr) {
                    var command_state = new SCWeb.core.CommandState(null, null, fmt_addr, lang);
                    var id = self.hash_addr(action_addr, command_state);
                    if (self.isWindowExist(id)) {
                        self.setWindowActive(id);
                    } else {
                        self.appendWindow(action_addr, command_state);
                        self.window_active_formats[action_addr] = command_state.format;
                        self.windows[self.hash_addr(action_addr, command_state.format)] = action_addr;
                    }
                }
            });

            $('#history-item-print').click(function () {
                if (SCWeb.ui.ArgumentsPanel.isArgumentAddState()) return;

                // get ctive window data
                var data = self.window_container.find("#" + self.active_window_id).html();

                var html = '<html><head>' + $('head').html() + '</head></html><body>' + data + '</body>';
                var styles = '';

                var DOCTYPE = "<!DOCTYPE html>"; // your doctype declaration
                var printPreview = window.open('about:blank', 'print_preview');
                var printDocument = printPreview.document;
                printDocument.open();
                printDocument.write(DOCTYPE +
                  '<html>' +
                  '<head>' + styles + '</head>' +
                  '<body class="print-preview">' + html + '</body>' +
                  '</html>');
                printDocument.close();
            });

            $('#history-item-link').popover({
                content: $.proxy(self.getUrlToCurrentWindow, self)
            });

            // listen translation events
            SCWeb.core.EventManager.subscribe("translation/update", this, this.updateTranslation);
            SCWeb.core.EventManager.subscribe("translation/get", this, function (objects) {
                $('#window-header-tools [sc_addr]').each(function (index, element) {
                    objects.push($(element).attr('sc_addr'));
                });
                $('#history-container [sc_addr]').each(function (index, element) {
                    objects.push($(element).attr('sc_addr'));
                });
            });

            resolve();
        });
        },

    getUrlToCurrentWindow: function () {
        return window.location.protocol + "//" + window.location.hostname + ":" + window.location.port + "/?action=" + this.active_history_addr;
    },

    // ----------- History ------------
    /**
     * Append new tab into history
     * @param {String} action_addr sc-addr of item to append into history
     * @param command_state
     */
    appendHistoryItem: function (action_addr, command_state) {
        // @todo check if tab exist        
        var tab_html = '<a class="list-group-item history-item ui-no-tooltip" sc_addr="' + action_addr + '">' +
            '<p>' + action_addr + '</p>' +
            '</a>';

        this.history_tabs.prepend(tab_html);

        // get translation and create window
        if (!command_state.format)
        {
            var ext_lang_addr = SCWeb.core.Main.getDefaultExternalLang();
            command_state.format = SCWeb.core.ComponentManager.getPrimaryFormatForExtLang(ext_lang_addr);
        }

        if (!command_state.lang)
            command_state.lang = SCWeb.core.Translation.getCurrentLanguage();

        if (command_state.format) {
            var id = this.hash_addr(action_addr, command_state.format, command_state.command_args)
            if (this.isWindowExist(id)) {
                this.setWindowActive(id);
            } else {
                this.appendWindow(action_addr, command_state);
                this.window_active_formats[action_addr] = command_state.format;
            }
        }

        this.setHistoryItemActive(action_addr);

        // setup input handlers
        var self = this;
        this.history_tabs.find("[sc_addr]").click(function (event) {
            var action_addr = $(this).attr('sc_addr');
            self.setHistoryItemActive(action_addr);
            self.setWindowActive(self.hash_addr(action_addr, self.window_active_formats[action_addr]));
        });

        // translate added item
        SCWeb.core.Translation.translate([action_addr]).then(function (namesMap) {
            value = namesMap[action_addr];
            if (value) {
                $(self.history_tabs_id + " [sc_addr='" + action_addr + "']").text(value);
            }
        });
    },

    /**
     * Removes specified history item
     * @param {String} addr sc-addr of item to remove from history
     */
    removeHistoryItem: function (addr) {
        this.history_tabs.find("[sc_addr='" + addr + "']").remove();
    },

    /**
     * Set new active history item
     * @param {String} addr sc-addr of history item
     */
    setHistoryItemActive: function (addr) {
        if (this.active_history_addr) {
            this.history_tabs.find("[sc_addr='" + this.active_history_addr + "']").removeClass('active').find('.histoy-item-btn').addClass('hidden');
        }

        this.active_history_addr = addr;
        this.history_tabs.find("[sc_addr='" + this.active_history_addr + "']").addClass('active').find('.histoy-item-btn').removeClass('hidden');
    },


    // ------------ Windows ------------
    /**
     * Append new window
     * @param action_addr
     * @param command_state
     */
    appendWindow: function (action_addr, command_state) {
        var self = this;
        SCWeb.ui.Locker.show();
        var f = function (addr, is_struct) {
            var id = self.hash_addr(action_addr, command_state.format);
            if (!self.isWindowExist(id)) {
                var window_id = 'window_' + action_addr + "_format_" + command_state.format;
                var window_html = '<div class="panel panel-default sc-window" id="' + id + '" sc_addr="' + action_addr + '" sc-addr-fmt="' + command_state.format + '">' +
                    '<div class="panel-body" id="' + window_id + '"></div>'
                '</div>';
                self.window_container.prepend(window_html);

                self.hideActiveWindow();
                self.windows.push(id);
                if (self.windows.length > self.MAX_WINDOWS) {
                    const lastWindowId = self.windows.shift();
                    delete self.sandboxes[lastWindowId]
                    self.removeWindow(lastWindowId);
                }
            }
            sandbox = self.sandboxes[id];
            if (!sandbox) {
                var sandbox = SCWeb.core.ComponentManager.createWindowSandboxByFormat({
                    format_addr: command_state.format,
                    addr: addr,
                    is_struct: is_struct,
                    container: window_id,
                    window_id: id,
                    command_state: command_state,
                    canEdit: true    //! TODO: check user rights
                });
            }
            if (sandbox) {
                self.sandboxes[id] = sandbox;
                self.setWindowActive(id);
            } else {
                self.showActiveWindow();
                throw "Error while create window";
            }
            SCWeb.ui.Locker.hide();
        };

        var translated = function () {
            SCWeb.core.Server.getResultTranslated(action_addr, command_state.format, command_state.lang, function (d) {
                f(d.link, false);
            });
        };

        if (SCWeb.core.ComponentManager.isStructSupported(command_state.format)) {
            // determine result structure
            window.scHelper.getResult(action_addr).then(function (addr) {
                f(addr, true);
            }).catch(function (v) {
                translated();
            });
        } else
            translated();
    },

    /**
     * Remove specified window
     * @param {String} addr sc-addr of window to remove
     */
    removeWindow: function (id) {
        this.window_container.find(`#${id}`).remove();
    },

    /**
     * Makes window with specified addr active
     * @param {String} addr sc-addr of window to make active
     */
    setWindowActive: function (id) {
        this.hideActiveWindow();
        this.active_window_id = id;
        this.showActiveWindow();
    },

    hideActiveWindow: function () {
        if (this.active_window_id)
            this.window_container.find("#" + this.active_window_id).addClass('hidden');
    },

    showActiveWindow: function () {
        if (this.active_window_id)
            this.window_container.find("#" + this.active_window_id).removeClass('hidden');
        SCWeb.ui.OpenComponentHandler.callOpenComponentCallback(this.active_window_id);
    },

    getActiveWindow: function (id) {
        if (this.active_window_id)
            return this.window_container.find("#" + this.active_window_id);
    },

    getActiveWindowId: function () {
        return this.active_window_id;
    },

    /*!
     * Genarate html for new window container
     * @param {String} containerId ID that will be set to container
     * @param {String} controlClasses Classes that will be added to controls
     * @param {String} containerClasses Classes that will be added to container
     * @param {String} addr sc-addr of window
     */
    generateWindowContainer: function (containerId, containerClasses, controlClasses, addr) {

        return '<div class="sc-content-wrap" id="' + containerId + '_wrap"> \
                    <div class="sc-content-controls ' + controlClasses + '" sc_addr="' + addr + '"> </div> \
                    <div id="' + containerId + '" class="sc-content ' + containerClasses + '"> </div> \
                </div>';
    },

    /**
     * Create viewers for specified sc-links
     * @param {Object} links Map of viewer containers (key: sc-link addr, value: id of container)
     */
    createViewersForScLinks: function (links) {
        return new Promise((resolve)=> {
            (function (links) {
                SCWeb.core.Server.getLinksFormat(links).then(
                  function (formats) {
                      let result = {};
                      for (const id in links) {
                          const link = links[id];

                          const fmt = formats[id];
                          const addr = link.addr;
                          const content = link.content;
                          const contentStyle = link.contentStyle;

                          if (fmt) {
                              const sandbox = SCWeb.core.ComponentManager.createWindowSandboxByFormat({
                                  format_addr: fmt,
                                  addr: addr,
                                  content: content,
                                  contentStyle: contentStyle,
                                  is_struct: false,
                                  container: id,
                                  canEdit: false
                              });
                              if (sandbox) {
                                  result[id] = sandbox;
                              }
                          }
                      }

                      resolve(result);
                  }
                );
            })(links);
        })
    },

    /** Create viewers for specified sc-structures
     * @param {Object} containers_map Map of viewer containers (id: id of container, value: {key: sc-struct addr, ext_lang_addr: sc-addr of external language}})
     */
    createViewersForScStructs: function (containers_map) {
        var res = {};
        for (var cntId in containers_map) {
            if (!containers_map.hasOwnProperty(cntId))
                continue;

            var info = containers_map[cntId];
            res[cntId] = SCWeb.core.ComponentManager.createWindowSandboxByExtLang({
                ext_lang_addr: info.ext_lang_addr,
                addr: info.addr,
                is_struct: true,
                container: cntId,
                canEdit: false
            });
        }
        return res;
    },


    // ---------- Translation listener interface ------------
    updateTranslation: function (namesMap) {
        // apply translation
        $('#window-header-tools [sc_addr]:not(.btn)').each(function (index, element) {
            var addr = $(element).attr('sc_addr');
            if (namesMap[addr]) {
                $(element).text(namesMap[addr]);
            }
        });

        $('#history-container [sc_addr]:not(.btn)').each(function (index, element) {
            var addr = $(element).attr('sc_addr');
            if (namesMap[addr]) {
                $(element).text(namesMap[addr]);
            }
        });

    },
};

SCWeb.ui.OpenComponentHandler = {

    events: {},

    subscribeComponent: function (windowId, callback) {
        this.events[windowId] = callback;
    },

    unsubscribeComponent: function (windowId) {
        delete this.events[windowId];
    },

    callOpenComponentCallback: function (windowId) {
        if (this.events.hasOwnProperty(windowId)) {
            this.events[windowId]();
        }
    }
};

SCWeb.ui.UserPanel = {

    /*!
     * Initialize user panel.
     * @param {Object} params Parameters for panel initialization.
     * There are required parameters:
     * - sc_addr - sc-addr of user
     * - is_authenticated - flag that have True value, in case when user is authenticated
     * - current_lang - sc-addr of used natural language
     */
    init: function (params) {
        return new Promise(resolve => {
            this.is_authenticated = params.user.is_authenticated;
            this.user_sc_addr = params.user.sc_addr;
            this.lang_mode_sc_addr = params.user.current_lang;
            this.default_ext_lang_sc_addr = params.user.default_ext_lang

            if (this.is_authenticated) {
                $('#auth-user-name').attr('sc_addr', this.user_sc_addr).text(this.user_sc_addr);
                $('#auth-user-lang').attr('sc_addr', this.lang_mode_sc_addr).text(this.lang_mode_sc_addr);
                $('#auth-user-ext-lang').attr('sc_addr', this.default_ext_lang_sc_addr).text(this.default_ext_lang_sc_addr);
            }

            // listen translation events
            SCWeb.core.EventManager.subscribe("translation/update", this, this.updateTranslation);
            SCWeb.core.EventManager.subscribe("translation/get", this, function (objects) {
                $('#auth-user-panel [sc_addr]').each(function (index, element) {
                    objects.push($(element).attr('sc_addr'));
                });
            });

            resolve();
        })
    },

    // ---------- Translation listener interface ------------
    updateTranslation: function (namesMap) {
        // apply translation
        $('#auth-user-panel [sc_addr]').each(function (index, element) {
            var addr = $(element).attr('sc_addr');
            if (namesMap[addr]) {
                $(element).text(namesMap[addr].replace('user::', '').replace('session::', ''));
            }
        });

    },


};

SCWeb.ui.ExpertModePanel = {

    init: function () {
        return new Promise(resolve => {
            var expert_mode_identifier = 'ui_expert_mode';
            this.expert_mode_container_id = '#' + 'expert_mode_container';
            var self = this;
            SCWeb.core.Server.resolveScAddr([expert_mode_identifier]).then(function (addrs) {
                var expert_mode_sc_addr = addrs[expert_mode_identifier];
                if (expert_mode_sc_addr) {
                    SCWeb.core.Server.resolveIdentifiers([expert_mode_sc_addr]).then(function (translation) {
                        $(self.expert_mode_container_id + ' label.normalLabel').
                        attr('sc_addr', expert_mode_sc_addr).text(translation[expert_mode_sc_addr]);

                        SCWeb.core.EventManager.subscribe("translation/update", self, self.updateTranslation);
                        SCWeb.core.EventManager.subscribe("translation/get", self, function (objects) {
                            $(self.expert_mode_container_id + ' [sc_addr]').each(function (index, element) {
                                objects.push($(element).attr('sc_addr'));
                            });
                        });
                        resolve();
                    });
                }
                else {
                    resolve();
                }
            });
        })
    },

    // ---------- Translation listener interface ------------
    updateTranslation: function (namesMap) {
        // apply translation
        $(this.expert_mode_container_id + ' [sc_addr]').each(function (index, element) {
            var addr = $(element).attr('sc_addr');
            if (namesMap[addr]) {
                $(element).text(namesMap[addr]);
            }
        });
    },
};

var expertModeCheckbox;
var modeSwitchingButtons;

var button;

$(document).ready(function () {
    SCWeb.core.ExpertModeEnabled = false;
    expertModeCheckbox = document.querySelector('#mode-switching-checkbox');
    modeSwitchingButtons = document.getElementsByClassName("mode-switching-panel")[0];
    if (expertModeCheckbox) {
      expertModeCheckbox.checked = SCWeb.core.ExpertModeEnabled;
      if (!expertModeCheckbox.checked) {
         modeSwitchingButtons.style.display = "none";
      }
      expertModeCheckbox.onclick = function () {
         modeSwitchingButtons.style.display = expertModeCheckbox.checked ? "" : "none";
         SCWeb.core.ExpertModeEnabled = expertModeCheckbox.checked;
         SCWeb.core.EventManager.emit("expert_mode_changed");
      };
   }
});
